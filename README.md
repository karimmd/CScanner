<h4>***** Updates1: Want to add some functions in the code so the scanner can show these lines in the output terminal screen, please check the file RATS-report.c,these lines are taken from RATS tool</h4>

    Total lines analyzed: 7453
    Total time 0.006267 seconds
    1189245 lines per second



<h4>****** Updates2: Need to find a way to link between the output file and the Safe Library.The safe library is named as "SafeLib.h".In the grammar file named as "y.y",we have included SafeLib.h but its not using the library.Please check the SafeLib.h file to see if there is any way to link it to the y.y file.Some pages from the Thesis</h4>

<a href="http://imgur.com/k2zCuQs"><img src="http://i.imgur.com/k2zCuQs.png" title="Hosted by imgur.com"/></a>
<a href="http://imgur.com/1sBTWq4"><img src="http://i.imgur.com/1sBTWq4.png" title="Hosted by imgur.com"/></a>




<h4>***** Updates3: Scanning the cpp (C++ source code) also not properly functioning. We need to find a way so that scanner can scan C++ codes also.</h4>

<h4>***** Updates4: Most of the Warning messages have been fixed, even the re-write process is working. But we still have to find a way for the less amount of false positives and false negatives. Probably need to test more vulnerable files.</h4>



<b>WE ARE DOING THIS PROJECT based on the paper</b> <a href="http://spectrum.library.concordia.ca/8387/" target="_blank"><strong>"A new approach for testing buffer overflow vulnerabilities in C and C++" by Alouneh, Sahel A"</strong></a>This is the Scanner Architecture <a href="http://imgur.com/2OLZx0W"><img src="http://i.imgur.com/2OLZx0W.png" title="Hosted by imgur.com"/></a>


<blockquote>PLEASE FOLLOW THIS LINK BELOW IF YOU WANT TO COMPILE THE SCANNER IN THE WINDOWS OS. IN LINUX FLEX,BISON AND GCC COMES WITH THE SYSTEM SO U DONT NEED TO INSTALL ANYTHING.</blockquote>

http://stackoverflow.com/questions/5456011/how-to-compile-lex-yacc-files-on-windows


First Use the <a href="http://en.wikipedia.org/wiki/Flex_lexical_analyser" target="_blank"><strong>FLEX</strong></a> tool to compile *.l file, Here it is l.l,the lexical file

<code>$ flex l.l</code>

then Use the <a href="http://en.wikipedia.org/wiki/GNU_Bison" target="_blank"><strong>BISON</strong></a> tool to compile *.y file, Here it is y.y,the parser file (this file is the heart of the program)

<code>$ bison -dy y.y</code>    (if u type bison --help,you can see,bison manual,normally we r using -dy ,but not sure if we should use some other append)


in the program We r having <blockquote>14 shift/reduce conflicts</blockquote>searching in google,we have found out two types of conflicts,shift/reduce and reduce/reduce,normally reduce/reduce is more complicated to resove. Here,shift/reduce conflict is related to the grammar of the y.y file.So,if u type bison -V y.y ,it will create an output file with an *.o extension where u can check which line or grammar is responsible.


In spite of having this conflict we were still able to compile the code,so not yet sure if this conflict is a big issue or not.

finally <a href="http://en.wikipedia.org/wiki/GNU_Compiler_Collection" target="_blank"><strong>GCC</strong></a> has been used to compile the final executable file

<code>$ gcc lex.yy.c y.tab.c -o test</code>   (here test is the application name)


Now to run the scanner you should

<code>$ ./test first.c second.c warnings.txt</code>

Here "second.c" is the re-writted safer version of the code. Even You can use the text extension instead of c extension. 

It means the first c(it can scan cpp extension too) is the file you want to scan, second.c is the safer version of the code,the scanner will try to produce and the warnings should be the vulnerability function alarm.If you check the y.y file,you can see some printf function containing those warnings.


<a href="http://imgur.com/riy0P1h"><img src="http://i.imgur.com/riy0P1h.png" title="Hosted by imgur.com"/></a>

Our Current Scan Result of Extensions.c from WuFtpd 2.6.2
<a href="http://imgur.com/fepnXdo"><img src="http://i.imgur.com/fepnXdo.png" title="Hosted by imgur.com"/></a>

******Updates: During scanning, we got the message 

<blockquote>"error: syntax error in line: 1082 and 1106 please check your function arguments!
*** NOW: if you are sure your code is correct, 
please insert // before your function call
in orderto ignore this syntax error"</blockquote>

So We modified line 1082 and 1106 for ignoring syntax error as the image below
<a href="http://imgur.com/Iqrk9Df"><img src="http://i.imgur.com/Iqrk9Df.png" title="Hosted by imgur.com"/></a>
