This project demonstrates a simple multithreaded application.

It revolves around a theoretical couple

Given the opening balance for the couple and two files containing the transactions for the husband and the wife,perform the transactions contained in the files on the opening balance.
If a withdrawal can't be successful due to insufficient balance, display 'Transaction declined'

The husband's transactions runs in the main thread whiles the wife's transaction runs in a separate thread

The program assumes that the first file is the husband's file and the second file is that of the wife's

The types of transactions possible are: deposit and withdraw

To specify a transaction in any of files, the syntax is as follows:

<Transaction_type> <amount>

where <Transaction_type> can be 'deposit' or 'withdraw'

and <amount> a positive integer

This project contains example transaction files, therefore, you can do your first run of the program bytyping on the command line:

./bank 0 husband.txt wife.txt
