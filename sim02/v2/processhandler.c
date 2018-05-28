#include "processhandler.h"

int meta_to_pcb_list(LinkedList* metaDataList, ProcessNode* phead, ConfigData* config)
{
	PCB* temp_pcb = NULL;
	ProcessNode* temp_process;
	MetaData* temp_meta;
	MetaData* tempNode;
	int PID = 0;

	MetaData* metaHead = metaDataList->head;
	while (metaHead != NULL)
	{
		tempNode = metaHead->next;
		//handles the start of a new process
		if (metaHead->command == 'A' && str_n_cmp(metaHead->operation, "start", 4) == 0)
		{
			// setup dummy data for a new PCB
			temp_pcb = malloc(sizeof(PCB));
			temp_pcb->state = NEW;
			temp_pcb->cycleTime = metaHead->cycleTime;
			temp_pcb->PID = PID++;
			temp_pcb->currentAction = metaHead;

			//handle adding the first process
			if (phead->process == NULL)
			{
				phead->process = temp_pcb;
			}
			else
			{
				temp_process = malloc(sizeof(ProcessNode));
				phead->next = temp_process;
				phead = phead->next;
				phead->process = temp_pcb;
				phead->next = NULL;
			}
		}
		//handles the end of a process
		else if (metaHead->command == 'A' && str_n_cmp(metaHead->operation, "end", 2) == 0)
		{
			metaHead->next = NULL;

			temp_meta = temp_pcb->currentAction;
			while (temp_meta != NULL)
			{
				// calculate cycle time
				// if IO meta
				if (temp_meta->command == 'I' || temp_meta->command == 'O')
				{
					temp_pcb->cycleTime += config->IOCT * temp_meta->cycleTime;
				}
				else if (temp_meta->command == 'M')
				{
					temp_pcb->cycleTime = 0;
				}
				else
				{
					temp_pcb->cycleTime += config->PCT * temp_meta->cycleTime;
				}
				temp_meta = temp_meta->next;
			}
		}
		metaHead = tempNode;
	}
	return 0;
}

int print_processes(ProcessNode* phead)
{
	while (phead != NULL)
	{
		printf("###PCB###\n");
		printf("Process ID %d\n", phead->process->PID);
		printf("Process cycle time %d\n", phead->process->cycleTime);

		MetaData* caction = phead->process->currentAction;
		while (caction != NULL)
		{
			printf("Action command %c\n", caction->command);
			printf("Action operation %s\n", caction->operation);
			printf("Action cycle time %d\n\n", caction->cycleTime);
			caction = caction->next;
		}

		phead = phead->next;
	}
	return 0;
}

int run(PCB* torun, OutputNode* output_head, char* timestr)
{
	torun->state = RUNNING;
	//accessTimer(1, timestr);
	char output_line[MAX_STRING];
	sprintf(output_line, "Time: %9s, Process %i set in Running state\n", timestr, torun->PID);
	add_output(output_line, output_head);
	output_line[0] = '\0';

	while (torun->currentAction != NULL)
	{
		if (torun->currentAction->command == 'M')
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, Memory management allocate action start\n", timestr, torun->PID);
			add_output(output_line, output_head);
			output_line[0] = '\0';
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, Memory management allocate action start\n", timestr, torun->PID);
			add_output(output_line, output_head);
			output_line[0] = '\0';
		}
		else if (torun->currentAction->command == 'I')
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, %s input start\n", timestr, torun->PID, torun->currentAction->operation);
			add_output(output_line, output_head);
			output_line[0] = '\0';
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, %s input end\n", timestr, torun->PID, torun->currentAction->operation);
			add_output(output_line, output_head);
			output_line[0] = '\0';
		}
		else if (torun->currentAction->command == 'O')
		{
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, %s output start\n", timestr, torun->PID, torun->currentAction->operation);
			add_output(output_line, output_head);
			output_line[0] = '\0';
			accessTimer(1, timestr);
			sprintf(output_line, "Time: %9s, Process %i, %s output end\n", timestr, torun->PID, torun->currentAction->operation);
			add_output(output_line, output_head);
			output_line[0] = '\0';
		}
		torun->currentAction = torun->currentAction->next;
	}
	// Set process to exit state.
	torun->state = EXIT;
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: Process %i set in Exit state\n", timestr, torun->PID);
	add_output(output_line, output_head);
	output_line[0] = '\0';

	return 0;
}

int fill_fcfsn(FCFSQueue* queue, ProcessNode* process_list)
{
	// if process list is empty
	if (process_list->process == NULL)
	{
		return -1;
	}
	else
	{
		while (process_list != NULL)
		{
			FCFSNode* new_node = (FCFSNode*)malloc(sizeof(FCFSNode));
			new_node->process = process_list->process;
			enqueue(queue, new_node, 1);
			process_list = process_list->next;
		}
	}
	return 0;
}

int enqueue(FCFSQueue* queue, FCFSNode* node, int priority)
{
	node->process->state = READY;
	if (queue->head == NULL)
	{
		queue->head = queue->tail = node;
	}
	else
	{
		queue->tail = queue->tail->next = node;
		queue->tail->next = NULL;
	}
	return 0;
}

PCB* dequeue(FCFSQueue* queue)
{
	PCB* ret = NULL;
	if (queue->head == NULL)
	{
		return NULL;
	}
	else
	{
		ret = queue->head->process;
		FCFSNode* next = queue->head->next;
		queue->head = next;
		if (queue->head == NULL)
		{
			queue->tail = NULL;
		}
	}
	return ret;
}

PCB* next_process(FCFSQueue* queue, char* strategy)
{
	if (str_n_cmp(strategy, "FCFS-N", 5) == 0)
	{
		PCB* process = dequeue(queue);
		return process;
	}
	return NULL;
}