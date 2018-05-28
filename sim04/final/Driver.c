#include "Driver.h"

int main(int argc, char *argv[])
{
	// basic input error checking
	if (argc != 2)
	{
		printf("Input error!\nFormat: ./program.exe config_file.cnf");
		return -1;
	}

	char *config_path = argv[1];
	Config config_data = {-1, -1, -1, -1, -1, "", "", "", ""};
	parse_config(config_path, &config_data);

	init_mmu(&config_data);

	OutputNode output_head = { "", NULL };
	char output_line[MAX_STRING];

	// var to hold time
	char timestr[SMALL_STRING];
	accessTimer(0, timestr);

	// put string into output line
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, System Start\n", timestr);
	// add output to list
	add_output(output_line, &output_head);
	// clear the output line
	output_line[0] = '\0';

	char *meta_path = config_data.metaFilePath;

	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: Begin PCB Creation\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';

	Process process_list = { -1, NEW, 0, NULL, NULL, NULL};
	parse_processes(meta_path, &process_list);
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: All processes now set in New state\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';
	
	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: All processes now set in Ready state\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';

	schedule_jobs(&config_data, &process_list, &output_head, timestr);

	accessTimer(1, timestr);
	sprintf(output_line, "Time: %9s, OS: System stop\n", timestr);
	add_output(output_line, &output_head);
	output_line[0] = '\0';
	
	handle_output(&config_data, &output_head);
	
}