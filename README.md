# Library Management System

Ένα απλό σύστημα διαχείρισης βιβλιοθήκης. Αυτό το πρόγραμμα επιτρέπει στους χρήστες να συνδεθούν και να εκτελέσουν διάφορες λειτουργίες, όπως προβολή, δανεισμό και επιστροφή βιβλίων.

## Roles

```bash
USER
```
Οι χρήστες μπορούν να δανείστουν, να επιστρέφουν και να αναζήτησουν βιβλία.
```bash
ADMIN
```
Ένας διαχειριστής μπορεί να διαχειριστή τη συλλογή βιβλίων και τη βάση δεδομένων των user.

## Features
• User login and authentication  
• Administrator login and authentication  
• Viewing all available books  
• Borrowing books  
• Returning books  
• Searching for books by name  
• Viewing all users (admin only)  
• Adding and removing books (admin only)  
• Adding and removing users (admin only)  
#    

# User Instructions

### Introduction Screen
``` bash
----------------------------------------------------
              Welcome to Bibioteca!
----------------------------------------------------
Please select one of the following options
1) Log in as User
2) Log in as Administrator
3) Exit
----------------------------------------------------
```
``` Select option 1```
### Sign In
``` bash
Please enter your user ID 1001
Please enter your password pw1
Welcome, Andreas!
```

### User Menu
```bash
----------------------------------------------------
What would you like to do
1) View all Books
2) Borrow a Book
3) Return a Book
4) Search for a Book by Name
5) Logout
----------------------------------------------------
```
## Examples
```1) View all Books```  
Displays all the books along with their book code, status (availableunavailable), and name.
```
Book code 300 ----- Status Available ----- Book Name To-Kill-a-Mockingbird  
Book code 301 ----- Status Available ----- Book Name 1984  
Book code 302 ----- Status NA ----- Book Name Pride-and-Prejudice  
Book code 303 ----- Status NA ----- Book Name The-Catcher-in-the-Rye  
Book code 304 ----- Status NA ----- Book Name The-Great-Gatsby  
Book code 305 ----- Status Available ----- Book Name Moby-Dick  
Book code 306 ----- Status Available ----- Book Name War-and-Peace  
Book code 307 ----- Status Available ----- Book Name The-Lord-of-the-Rings  
Book code 308 ----- Status Available ----- Book Name Brave-New-World
```   
  
```2) Borrow a Book```  
To borrow a book, you need to know its book code.
``` 
Please enter the book code of the book you want to borrow
```
For example, to borrow the book with code 307, The Lord of the Rings
```
Please enter the book code of the book you want to borrow 307
Great choice! You have booked The-Lord-of-the-Rings.
```
Now, the book with code 307 is no longer available
```
Book code 306 ----- Status Available ----- Book Name War-and-Peace
Book code 307 ----- Status NA ----- Book Name The-Lord-of-the-Rings
Book code 308 ----- Status Available ----- Book Name Brave-New-World
```

```3) Return a Book```  
To return a book, you also need to know its book code. (The book can only be returned by the user who borrowed it.)
```
Please enter the book code of the book you want to return 307
Thank you for returning the book 'The-Lord-of-the-Rings' with book code '307'.
```
```4) Search for a Book by Name```  
Search for a book by its name or a keyword.
```
Enter the name of the book you are looking for
```
For example, using the keyword the will display all books that contain the in their title
```
Enter the name of the book you are looking for The
Book code 303 ----- Status NA ----- Book Name The-Catcher-in-the-Rye
Book code 304 ----- Status NA ----- Book Name The-Great-Gatsby
Book code 307 ----- Status Available ----- Book Name The-Lord-of-the-Rings
Book code 309 ----- Status Available ----- Book Name Harry-Potter-and-the-Sorcerer's-Stone
Book code 311 ----- Status Available ----- Book Name The-Hobbit
Book code 312 ----- Status Available ----- Book Name The-Hitchhiker's-Guide-to-the-Galaxy
Book code 315 ----- Status Available ----- Book Name The-Road
Book code 318 ----- Status Available ----- Book Name Wuthering-Heights
Book code 319 ----- Status Available ----- Book Name The-Alchemist
Book code 320 ----- Status Available ----- Book Name The-picture-of-Dorian-Gray
```
```5) Logout```   
Logs the current user out.

==========================================================================================

# Admin Instructions  

### Introduction Screen
``` bash
----------------------------------------------------
              Welcome to Bibioteca!
----------------------------------------------------
Please select one of the following options
1) Log in as User
2) Log in as Administrator
3) Exit
----------------------------------------------------
```
``` Select option 2```
### Sign In
``` bash
Please enter your admin ID admin
Please enter your password adminpass
Welcome, Admin!
```
### Admin Menu
```bash
----------------------------------------------------
What would you like to do
1) View all Books
2) Add a Book
3) Remove a Book
4) View all Users
5) Add a User
6) Remove a User
7) Logout
----------------------------------------------------
```




## Examples
```1) View all Books```  
Displays all the books along with their book code, status (availableunavailable), and name.
```
Book code 300 ----- Status Available ----- Book Name To-Kill-a-Mockingbird
Book code 301 ----- Status Available ----- Book Name 1984
Book code 302 ----- Status Available ----- Book Name Pride-and-Prejudice
Book code 303 ----- Status Available ----- Book Name The-Catcher-in-the-Rye
Book code 304 ----- Status Available ----- Book Name The-Great-Gatsby
Book code 305 ----- Status Available ----- Book Name Moby-Dick
Book code 306 ----- Status Available ----- Book Name War-and-Peace
Book code 307 ----- Status Available ----- Book Name The-Lord-of-the-Rings
Book code 308 ----- Status Available ----- Book Name Brave-New-World
Book code 309 ----- Status Available ----- Book Name Harry-Potter-and-the-Sorcerer's-Stone
Book code 310 ----- Status Available ----- Book Name Crime-and-Punishment
Book code 311 ----- Status Available ----- Book Name The-Hobbit
Book code 312 ----- Status Available ----- Book Name The-Hitchhiker's-Guide-to-the-Galaxy
Book code 313 ----- Status Available ----- Book Name Fahrenheit-451
Book code 314 ----- Status Available ----- Book Name Catch-22
Book code 315 ----- Status Available ----- Book Name The-Road
Book code 316 ----- Status Available ----- Book Name Beloved
Book code 317 ----- Status Available ----- Book Name Slaughterhouse-Five
Book code 318 ----- Status Available ----- Book Name Wuthering-Heights
Book code 319 ----- Status Available ----- Book Name The-Alchemist
Book code 320 ----- Status Available ----- Book Name The-picture-of-Dorian-Gray
Book code 321 ----- Status Available ----- Book Name David-Copperfield
```   
  
```2) Add a book```   
Add a new book to the database.
```
Enter the name of the book
```
For example, adding a book named To the Lighthouse
```
Enter the name of the book To the Lighthouse
Book added successfully.
```
Updated book list
```
Book code 320 ----- Status Available ----- Book Name The-picture-of-Dorian-Gray
Book code 321 ----- Status Available ----- Book Name David-Copperfield
Book code 322 ----- Status Available ----- Book Name To-the-Lighthouse       ----
```

```3) Remove a Book```  
Remove a book from the database.
```
Enter the book code to remove
```
For example, removing the book with code 322
```
Enter the book code to remove 322
Book 'To-the-Lighthouse' with code 322 removed.
```

```4) View all Users```  
View all users along with their IDs.
```
ID 1000 ----- User Christos
ID 1001 ----- User Andreas
ID 1002 ----- User Giorgos
ID 1003 ----- User Marios
```

```5) Add a User```   
Add a new user by entering their name and assigning a password.
```
Enter name
Enter password
```
For example, adding a user named Marina
```
Enter name Marina
Enter password pw9
User added successfully. Their ID is 1005
```

```6) Remove a User```  
Remove a user by entering their User ID.
```
Enter the user ID to remove
```
For example, removing the user with ID 1005
```
Enter the user ID to remove 1005
User 'Marina' with ID 1005 removed.
```

```7) Logout```  
Logs the current user out."# Library-Management-System" 
