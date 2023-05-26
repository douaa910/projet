#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[50];
    char Author_name[50];
    int reference_number;
    int quantity;
    float price;
    char size[20];
} BOOK;
typedef struct {
    int ID;
    char first_name[50];
    char last_name[50];
    float purchase[3];
    int purchase_history;
} Customer;
void addBook(BOOK book[], int *numBook);

void modifyBookQuantity(BOOK book[], int numBook);
void addCustomer(Customer customers[], int *numCustomers);
int searchCustomer(Customer customers[], int numCustomers);
void saveBook(BOOK book[], int numBook);
void saveCustomers(Customer customers[], int numCustomers);
void loadBook(BOOK book[], int *numBook);
void loadCustomers(Customer customers[], int *numCustomers);
int doesReferenceExist(BOOK book[], int numBook, int reference);
void displayLowStockBook(BOOK book[], int numBook);
int countBook(BOOK book[],int numBook , int capacite_maximale);




void displayLastPurchases(Customer customers[] , int clientId);
float TotalPrice(Customer customers[] , int clientId);



int EnterInt(const char* message) {
    int naturelNum;
    printf("%s", message);

    while (scanf("%d", &naturelNum) != 1 ) {
        printf("INVALID ENTRY. TRY AGAIN WITH NATUREL NUMBER : ");
        while (getchar() != '\n'); 
                                       }
    return naturelNum;
}

int countBook(BOOK book[], int numBook , int capacite_maximale){
  int occupstock =0;
  for(int i = 0;i < numBook ; i++){
    int requested_places = 0;
    if(strcmp(book[i].size , "little") == 0){
      requested_places = book[i].quantity;  
                                            }
    else if(strcmp(book[i].size , "meduim(PAPERBACK)") == 0){
      requested_places = book[i].quantity*2;
                                                            }
    else if(strcmp(book[i].size , "big(HARDBACK)") == 0){
      requested_places = book[i].quantity*4;
                                                         }
    if(occupstock + requested_places > capacite_maximale){
      printf("The requested amount of the stock surpass the maximal capacity of the stock. \n");
      return -1;
                                                        }
    occupstock+=requested_places;
                                  }
  int remainStock = capacite_maximale - occupstock;
  printf("The remaining stock is %d.\n",remainStock);
return remainStock;
}

int doesReferenceExist(BOOK book[], int numBook, int reference) {
    for (int i = 0; i < numBook; i++) {
        if (book[i].reference_number == reference) {
            return 1;
                                                   }
                                      }
    return 0;
}

void addBook(BOOK book[], int *numBook) {
    BOOK newBook;
    int capacite_maximale;
    int EmptyStock = countBook(book , *numBook,capacite_maximale);
    printf("\n=== Adding a new book ===\n");
    printf("Book name : ");
    scanf("%s", newBook.name);
    printf("\n");
    printf("Author's name : \n");
    scanf("%s",newBook.Author_name);
    printf("\n");
     do {
        printf("Reference number : ");
        scanf("%d", &newBook.reference_number);
        printf("\n");
if (doesReferenceExist(book, *numBook, newBook.reference_number)) {
            printf("La référence existe déjà. Veuillez en choisir une autre.\n");
        }
    }while(doesReferenceExist(book, *numBook, newBook.reference_number));

    printf("Quantity : ");
    scanf("%d", &newBook.quantity);
    printf("\n");
    printf("Price : ");
    scanf("%f", &newBook.price);
    printf("\n");
    printf("Book size (little , meduim(PAPERBACK) , big(HARDBACK) ) :\n ");
    scanf("%s", newBook.size);
  if((strcmp(newBook.size , "little")==0) && EmptyStock < newBook.quantity){
    printf("No space left, please enter an inferior value. \n");
                 }
  else if((strcmp(newBook.size , "meduim(PAPERBACK)")==0) && EmptyStock < 2*newBook.quantity){
    printf("No space left, please enter an inferior value. \n");
                               }
  else if((strcmp(newBook.size , "big(HARDBACK)")==0) && EmptyStock < 4*newBook.quantity){
    printf("No space left, please enter an inferior value. \n");
                   }
  else{
    book[*numBook] = newBook;
    (*numBook)++;  
       printf("Book added succesfully. \n");
      }
}




int main(){

    BOOK book[100];
    Customer customers[100];
    int numBook = 0;
    int numCustomers = 0;
    int modeChoice, mainChoice;
    int totalbook;
    Customer CLIENT;
    int clientId;
    int buyBook;
    int capacite_maximale = 1000;

    printf("       ╔════════════════╗ \n");
    printf("       ║   CY Library   ║ \n");
    printf("       ║      Shop      ║ \n");
    printf("       ╚════════════════╝ \n");

    loadCustomers(customers, &numCustomers);
    loadBook(book , &numBook);
    do {
        printf("=== CY Library Managment ===\n");
        printf("Mode :\n");
        printf("1. Management of the Stock \n");
        printf("2. Purchase / Client Mode \n");
        printf("3. Leave\n");
        printf(" Choice : ");
        scanf("%d", &modeChoice);
        switch (modeChoice) {
            case 1:
                do {
                    printf("======= Stock Managment =======\n");
                    printf("1. Add a book \n");
                    printf("2. Search a book \n");
                    printf("3. Modify the quantity of a book \n");
                    printf("4. display all the books with low stock \n");
                    printf("5. display the remaining stock \n");
                    printf("6. Back \n");
                    printf("Choice : ");
                    mainChoice=EnterInt("");
                    switch (mainChoice) {
                        case 1:
                            addBook(book, &numBook);
                            saveBook(book, numBook);
                            break;
                        case 2:
                            searchBook(book, numBook);
                            break;
                        case 3:
                            modifyBookQuantity(book, numBook);
                            saveBook(book, numBook);
                            break;
                        case 4:
                            displayLowStockBook(book, numBook);
                            break;
                        case 5:
                          loadBook(book , &numBook);
                        countBook(book , numBook , capacite_maximale);
                          
                       break;
                       case 6:
                       printf("Return to the main menu. \n");
                       break;
                        default:
                            printf("INVALID CHOICE !! PLESAE TRY AGAIN WITH ANOTHER CHOICE \n");
                            break;
                    }
                    printf("\n");
                } while (mainChoice != 6);
                break;
            case 2:
                do {
                    printf("======= Purchase Mode =======\n");
                    printf("1. LOG IN with an existing account \n");
                    printf("2. SIGN IN (create your CY Library account) \n");
                    printf("3. Retun\n");
                    printf("Choice : ");
                    mainChoice = EnterInt("");
                    switch (mainChoice) {
                        
                        case 1:
                            
                            clientId=searchCustomer(customers, numCustomers);
                            if(clientId = 0){
                              printf("This client ID does not exist");
                                            }
                            else{
                              displayLastPurchases(customers  ,clientId);
                              TotalPrice(customers , clientId);
                              printf("Do you want to buy a new book?\n");
                              printf("if YES tap 1 / if NO tap 0 \n");
                              scanf("%d",&buyBook);
                              if(buyBook){
                                purchaseProduct(book);
                                displayLastPurchases(customers ,clientId);
                                TotalPrice(customers , clientId);
                                         }
                              else{
                                printf("Farwell\n");
                                  }
                                }
                            break;
                        case 2:
                          addCustomer(customers, &numCustomers);
                          saveCustomers(customers, numCustomers);
                          printf("Do you want to buy a new book?\n");
                              printf("if YES tap 1 / if NO tap 0 \n");
                              scanf("%d",&buyBook);
                              if(buyBook){
                                purchaseProduct(book);
                                displayLastPurchases(customers ,clientId);
                                TotalPrice(customers , clientId);
                                         }
                              else{
                                printf("Farwell\n");
                                  }
    
                            break;
                        case 3:
                            printf("Return to the main menu. \n");
                        default:
                            printf("INVALID CHOICE !!! PLEASE TRY AGAIN WITH A VALID CHOICE.\n");
                            break;
                    }
                    printf("\n");
                } while (mainChoice != 3);
                break;
            case 3:
                printf("Farwell\n");
                break;
            default:
                printf("INVALID CHOICE !!! PLEASE TRY AGAIN WITH A VALID CHOICE.\n");
                break;
        }
        printf("\n");
    } while (modeChoice != 3);
    
  return 0;
}

void displayLowStockBook(BOOK book[], int numBook)
{
    printf("======= Books with low stock =======\n");
    for (int i = 0; i < numBook; i++) {
        if ((book[i].quantity == 0) || (book[i].quantity != 0 && book[i].quantity < 5) ){
            printf("Name of the book : %s\n", book[i].name);
            printf("Reference number : %d\n", book[i].reference_number);
            printf("Quantity : %d\n", book[i].quantity);
            printf("Price : %.2f\n", book[i].price);
            printf("Size of the book : %s\n", book[i].size);
            printf("\n");
                        }
                                     }
}

void saveBook(BOOK book[], int numBook) {
    FILE *file = fopen("Library.txt", "w");
    if (file == NULL) {
        printf("\n EROOR !!! THE REQUESTED FILE CANNOT BE OPEN \n");
        return;
                      }
    for (int i = 0; i < numBook; i++) {
        fprintf(file , "%s, " , book[i].name);
        fprintf(file , "%s, " , book[i].Author_name);
        fprintf(file , "%d, " , book[i].reference_number);
        fprintf(file , "%d, " , book[i].quantity);
        fprintf(file , "%.2f, " , book[i].price);
        fprintf(file , "%s. \n" , book[i].size);
                                      }
    fclose(file);
}

void saveCustomers(Customer customers[], int numCustomers) {
    FILE *file = fopen("customers.txt", "w");
    if (file == NULL) {
        printf("\n ERROR !!! THE REQUESTED FILE CANNOT BE OPEN \n");
        return;
                      }
    for (int i = 0; i < numCustomers; i++) {
        fprintf(file, "%d , %s, %s, %d \n",customers[i].ID, customers[i].first_name, customers[i].last_name, customers[i].purchase_history);
                                           }
    fclose(file);
}

void loadCustomers(Customer customers[], int *numCustomers) {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        printf("\n ERROR !!! THE REQUESTED FILE CANNOT BE OPEN \n");
        return;
                      }
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, " %d , %[^,] , %[^,], %d \n", &customers[i].ID , customers[i].first_name, customers[i].last_name,&customers[i].purchase_history);
        i++;
                                            }
    *numCustomers = i;
    fclose(file);
}
void loadBook(BOOK book[], int *numBook) {
    FILE *file = fopen("Library.txt", "r");
    if (file == NULL) {
        printf("\n ERROR !!! THE REQUESTED FILE CANNOT BE OPEN \n");
        return;
                      }
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %d, %d, %f, %[^.] \n", book[i].name, book[i].Author_name, &book[i].reference_number, &book[i].quantity, &book[i].price, book[i].size);
        i++;
                                            }
    *numBook = i;
    fclose(file);
}

void modifyBookQuantity(BOOK book[], int numBook) {
    int reference;
    int newQuantity;
    int capacite_maximale;
    int EmptyStock = countBook(book,numBook,capacite_maximale);
    printf("======= Modify the quantity of a book =======\n");
    printf("Reference number : ");
    scanf("%d", &reference);
    printf("\n");
    for (int i = 0; i < numBook; i++) {
        if (book[i].reference_number == reference) {
            printf("The actual quantity of the requested book is : %d\n", book[i].quantity);
            printf("New stock : ");
            scanf("%d", &newQuantity);
          if((strcmp(book[i].size , "little")==0) && EmptyStock + book[i].quantity < newQuantity){
    printf("No space left, please enter an inferior value. \n");

                               }
  else if((strcmp(book[i].size , "meduim(PAPERBACK)")==0) && EmptyStock + 2*book[i].quantity< 2*newQuantity){
    printf("No space left, please enter an inferior value. \n");
  }
  else if((strcmp(book[i].size , "big(HARDBACK)")==0) && EmptyStock + 4*book[i].quantity < 4*newQuantity){
    printf("No space left, please enter an inferior value. \n");
                                     }

  else{ 
    book[i].quantity = newQuantity;
    printf("Book added succesfully. \n");
      }          
            return;
        }
    }
    printf("BOOK NOT FOUND.\n");
}

void addCustomer(Customer customers[], int *numCustomers) {
    Customer newCustomer;
    printf("======= Add a new client =======\n");
    printf("Enter an ID : ");
    scanf("%d",newCustomer.ID);
    printf("\n");
    printf("Client's name : ");
    scanf("%s", newCustomer.first_name);
    printf("\n");
    printf("Client's last name : ");
    scanf("%s", newCustomer.last_name);
    printf("\n");
    printf("Purchase History : ");
    scanf("%d",newCustomer.purchase_history);
    customers[*numCustomers] = newCustomer;
    (*numCustomers);
    printf("Client added succefully. \n");
}

int searchCustomer(Customer customers[], int numCustomers) {
    char firstName[50];
    int f = 0;
    char lastName[50];
    int id;
    printf("======= Search a client =======\n");
    printf("Enter your ID : ");
    scanf("%d",&id);
    printf("\n");
    printf("Enter your First Name : ");
    scanf("%s", firstName);
    printf("\n");
    printf("Enter your Last Lame : ");
    scanf("%s", lastName);
    printf("\n");
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].first_name, firstName) == 0 && strcmp(customers[i].last_name, lastName) == 0 && strcmp(customers[i].ID , id) == 0) {
            printf("CLIENT FOUND. \n");
            printf("======= Clients details =======\n");
            printf("Client's ID : %d \n",customers[i].ID);
            printf("First Name : %s\n", customers[i].first_name);
            printf("Last Name : %s\n", customers[i].last_name);
            printf("Purchase History : %d \n", customers[i].purchase_history);
            return 1;
                                               }
    
    printf("CLIENT NOT FOUND. \n");
  return 0;
}
}


void deleteCustomer(Customer customers[], int *numCustomers){
  char firstname[50];
  char lastname[50];
  int id;
  int found = 0;
  printf("======= Remove Client ======= \n");
  printf("Enter your ID : ");
  scanf("%d",&id);
  printf("\n");
  printf("Enter your First Name : ");
  scanf("%s",firstname);
  printf("\n");
  printf("Enter your Last Name : ");
  scanf("%s",lastname);
  printf("\n");

  for (int i=0 ; i< *numCustomers ; i++){
    if (strcmp(customers[i].first_name, firstname) == 0 && strcmp(customers[i].last_name, lastname) == 0 && strcmp(customers[i].ID, id)== 0){
      for (int j = i; j < *numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
                                                  }
            (*numCustomers)--;
            found = 1;
            break;
                                              }
                                        }
  if(found){
    printf("Client's account has been deleted succesfully. \n");
           }
  else{
    printf("CLIENT NOT FOUND. \n");
      }
}

int searchBook(BOOK book[], int numBook){
    int reference;
    int i;
    printf("======= Search a book =======\n");
    printf("Reference number : ");
    scanf("%d", &reference);
    
    for(int i=0 ; i<numBook ; i++) {
        if(book[i].reference_number == reference){
            printf("BOOK FOUND. \n");
            printf("======= Book Details =======\n");
            printf("Book Name : %s\n", book[i].name);
            printf("The author of the book : %s\n",book[i].Author_name);
            printf("Refernce number : %d\n", book[i].reference_number);
            printf("Quantity : %d\n", book[i].quantity);
            printf("Price : %.2f\n", book[i].price);
            printf("%s size : %s\n",book[i].name, book[i].size);
          return 1;
                                                   }
      
                                    }
  printf("BOOK NOT FOUND. \n");
  return 0;
} 

void purchaseProduct(BOOK book[], int numBook){
  int amount;
  char bookname[50];
  printf("What is the name of the book you want to buy? \n");
  scanf("%s",bookname);
  printf("how many?\n");
  scanf("%d",&amount);
    for(int i=0 ; i<numBook ; i++){
    int productInd = searchBook(book, numBook);
    if (productInd == 0) {
        printf("The requested book "%s" is not available in the stock.\n",book[i].name);
        return;
                         }
    if (book[i].quantity < amount) {
        printf("The requested amount is unavailable at the moment. \n");
        return;
                                 }
    book[i].quantity -= amount;
    printf("Purchase of %s done succesfully.\n",book[i].name);
                                 }
}
void displayLastPurchases(Customer customers[] , int clientId){
    if (customers[clientId].purchase_history == 0) {
        printf("You have not bought anything yet.\n");
        return;
                                                   }
    printf("The three last purchases of %s %s :\n", customers[clientId].first_name,customers[clientId].last_name);
    int i;
    for (i = customers[clientId].purchase_history - 1 ; i >= 0 && i >= customers[clientId].purchase_history - 3 ; i--) {
        printf("- Book %d : %.2f EUR\n", i + 1, customers[clientId].purchase[i]);
                                                   }
}

float TotalPrice(Customer customers[] , int clientId) {
    float total = 0.0;
    for (int i = 0; i < customers[clientId].purchase_history ; i++) {
        total += customers[clientId].purchase[i];
                                                                    }
    return total;
}