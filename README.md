# Comparing Predictions
Simple script to find optimal predictions based on user input. Currently supports finding a maximum and insertion sorting.
Maximum: User provides a .txt file which contains a list of all predictions to be compared separated by newlines. An interactive insertion sort algorithm will then run prompting the user to compare two predictions. This continues until the the maximum is found. Outputs are written to a file with the same name, appended with 
"maximum_results". If the user quits in the middle of the analysis, the state is saved and the user can start from where they left off. 


Insertion Sorting: User provides a .txt file which contains a list of all predictions to be compared separated by newlines, along with the --sorting option. An interactive insertion sort algorithm will then run, prompting the user to compare two predictions. This continues until the sort is complete. Outputs are written to a file with the same name, appended with 
"sorted_results". If the user quits in the middle of the analysis, the state is saved and the user can start from where they left off. 
