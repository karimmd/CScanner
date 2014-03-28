int main()
{
char line[100];
char filename1[14]="c:\\file1.txt";
char filename2[6];
char filename3[30];

cout << "to open the file.txt,enter a word of 7 character at most:\n";
cin >> filename3;

strcpy (filename2,filename3);

ifstream fin;
fin.open(filename1);

cout << "***********************************************\n";
cout << "this is the content of file1.txt that you want to be open:\n";
cout << "***********************************************\n";

while (! fin.eof())
{
  fin.getline (line,100);
  cout << line << endl;
}

fin.close();
return 0;

}
