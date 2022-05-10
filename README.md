# Meeting-Planner-C++
Input and Output:
• The inputs will be provided via an input text le. The le will have commands (ADD,Find,MOD,DEL,Print)
each on a separate line.
• The planner should print its outputs (and messages) on the screen AND in an output text
le.
• Each output/message (whether on screen or in output le) should be on a separate line.
• The names of the input and output text les will be provided as inputs when running the
program as follows.

                p2.exe Input.txt Output.txt

The above line means that the program should read from Input.txt and create a le Output.txt
and print its outputs in it. The output should also be printed on screen. If a le with the
name Output.txt already exists, the program should overwrite it.




Example Case 1:
Input: p2.exe In1.txt Out1.txt
Output: Conict 5 10
"Physics Lecture 1" 5 9
"Math Section" 5 10
"Club_meeting" 5 11
"Movies" 100 20
"Math Section"
Empty 7 13
Empty 10 10
"Physics Lecture 1" 5 9
"Math Section" 5 10
"Club_meeting 5 11
"Movies" 100 20
Invalid day
"Physics Lecture 1" 5 9
"Math Section" 5 10
"Club_meeting" 5 11
Invalid hour
Invalid command
"Physics Lecture 1" 5 9
"Math Section" 5 10
"Club_meeting" 5 11
"Lunch" 10 4

The program should print its output on screen and also create le Out1.txt and
print the same output in it.
