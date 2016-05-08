# Logika-zadanie-3
This is the first task from the third homework for logic by Klaudia Knafel. It is prepared to by run on linux platform. 
The actual program is named condition.cpp. You can compile it with g++ ('g++ -o condition.exe condition.cpp' as default for the test program). 
The program includes complicated logic condition for the parameters wchich are given to the program (6 intigers).
It checks whether the first one is less than the second one, the third one is different from zero and one of parameters (fourth or fifth or sixth) is evenly divisible by the third parameter. If the condition is fulfilled program returns first_parameter-second_parameter+fourth_parameter%third_parameter+fifth_parameter%thrid_parameter+sixth_parameter%third_parameter. In other case it returns first_parameter-second_parameter. 
Test is a script that checks the results from the program condition.exe with expected results (if you compile condition to the file with different name than "condition.exe", then give its name as paramater to test (for example 'bash test ./name'). If results are different than expected then it prints out the input, the output and expected output.
Negated.cpp is the same program as condition but with negated condition. You can also use "test" to check negated, by running test with parameter ./negated.exe (if you compile negated by 'g++ -o negated.exe negated.cpp'). 
