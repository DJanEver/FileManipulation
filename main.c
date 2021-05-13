
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#define CHAR_ARRAY_SIZE 50
#define MAX_PATIENT_ID_IN_ROOM 5



//***************************************************************
// Struct.
//***************************************************************

//Patient Struct
struct Patient{
    long int patientID;
    char firstName[CHAR_ARRAY_SIZE];
    char lastName[CHAR_ARRAY_SIZE];
    char *covidStatus;
    int birthYear;
    char adDis[CHAR_ARRAY_SIZE];
};

//Rooms Struct
struct Room{
    int roomID;
    char *respiratorCheck;
    int roomBeds;
    char *roomHelp;
    long int patientIDS[MAX_PATIENT_ID_IN_ROOM];
};

//***************************************************************
// Functions
//***************************************************************
bool readFiles();
bool createFiles();
bool NameEntered(const char *string);
void patientsOptions();
void patientCovidStatusOptions();
void operationsP(const int *choice);
void addPatient();
struct Patient *collectPatientInfo( struct Patient *patient);
long int  checkGeneratedPatientID();
void checkPtr(void *ptr);
long int patientIDConverter(const char *ID);
int fileLength(FILE *ptr, char *line);
char *patientCovidStatus(const int *ptr);
void  roomsOptions();
void operationsR(const int *choice);
void addEmptyRoom();
struct Room *collectRoomInfo(struct Room *room);
int checkGeneratedRoomID();
int roomIDConverter(const char *ID);
char *roomResCheck(const int *ptr);
char *roomHelpCheck(const int *ptr);
void addRoomWithPatients();
bool checkRoomID(const int *ptr);
void pFileUpdate();
void deletePatient();
bool checkPatientId(const long int *ptr);
int getDelePatientLine(const long int *ptr);
void changePatientStatus();
struct Patient *splintPatientLine(const char *line);
struct Room *splintRoomLine(const char *line);
bool criticalRoomCheck(struct Room *room);
void aiStorePatientInRoom();
int getDeleRoomLine(const int *ptr);
bool severeRoomCheck(struct Room *room);
bool roomWithBedCheck(struct Room *room);
bool roomWithBedDoctorCheck(struct Room *room);
bool roomWithBedNurseCheck(struct Room *room);
void displayPatients();
void generateRoomAdmittanceAgeReport();
void saveRoomAdmittanceAgeReport(const int *ptrOne, const int *ptrTwo, const int *ptrThree,
                                 const int *ptrFour, const int* choice);
void covidStatusReport();
void saveCovidReport(const int *ptrOne, const int *ptrTwo, const int *ptrThree,
                     const int *ptrFour, const int *ptrFive, const int* choice);
void aiDeletePatient( FILE *filePtr, FILE *tempFile,const long int *ptr);
bool checkRoomForPatient(const long int *ptr);
void sysClearScreen();
int getRoomIDToDelPatient(const long int *ptr);


//***************************************************************
// main
//***************************************************************
int main(){
    errno = 0; // errno deals with error handling in c
    //character pointer.
    char *fileName = (char*)malloc(10 *sizeof(char)); //allocating memory to the file pointer
    bool flag;
    //seeding the rand function.
    srand(time(NULL));

    //checking if files already exist.
    if(!readFiles()) {
        //Checking if files were created.
        if (!createFiles()) {
            puts("Error. Files were not created.\n");
            //will exit the program id the files were not created
            exit(EXIT_FAILURE);
        }// end if
    }// end if

    //In a infinite loop for now just to test.
    do {

        sysClearScreen();//this function clears the screen.

        printf("\t\t\tWelcome User.\n");
        //asking user to enter the file name they want to edit.
        printf("***************************************************");
        printf("\n*   Enter the name of the file you want to edit   ");
        printf("\n*       Type patients for the patient file        ");
        printf("\n*  Type rooms for the room file or exit to quite  ");
        printf("\n* >> ");

        //checking filename pointer
        checkPtr(fileName);

        scanf("%s", fileName);
        flag = NameEntered(fileName);// NameEntered checks the string then goes into that operation

    }while(flag);

    free(fileName);// freeing all the memory that was allocated.
    return 0;
}

//***************************************************************
// Options for the patient file.
//***************************************************************
void patientsOptions(){
    printf("***************************************************");
    printf("\n\t\t<-----Options----->\n");
    printf("***************************************************");
    printf("\n* 1.Add Patient");
    printf("\n* 2.Display Patient Report");
    printf("\n* 3.Patient File Update");
    printf("\n* 4.AI Room Assignment");
    printf("\n* 5.Covid Status Report");
    printf("\n* 6.Go Back");
    printf("\n* >> ");
}

//***************************************************************
//Options for the patient status.
//***************************************************************
void patientCovidStatusOptions(){
    printf("***************************************************");
    printf("\n\t\t<-----Options----->\n");
    printf("***************************************************");
    printf("\nPlease Select a option");
    printf("\n* 1.None");
    printf("\n* 2.Mild");
    printf("\n* 3.Average");
    printf("\n* 4.Severe");
    printf("\n* 5.Critical");
    printf("\n* >> ");

}

//***************************************************************
// Options for the room file.
//***************************************************************
void roomsOptions(){
    printf("***************************************************");
    printf("\n\t\t<-----Options----->\n");
    printf("***************************************************");
    printf("\n* 1.Add empty room");
    printf("\n* 2.Add room with patient");
    printf("\n* 3.Room admittance by age group Report");
    printf("\n* 6.Go Back");
    printf("\n* >> ");
}

//***************************************************************
//Will return true if files already exist.
//***************************************************************
bool readFiles(){

    //Creating Files
    FILE *patientFilePtr = fopen("patients.txt", "r");
    FILE *roomFilePtr = fopen("rooms.txt", "r");

    bool flag = false;

    //checking if file pointers are null
    if(patientFilePtr != NULL && roomFilePtr != NULL){
        flag = true;
    }// end if

    //Closes the files.
    fclose(patientFilePtr);
    fclose(roomFilePtr);

    return flag;
}// end function

//***************************************************************
//Will return true if files were created.
//***************************************************************
bool createFiles(){

    //Creating Files
    FILE *patientFilePtr = fopen("patients.txt", "w");
    FILE *roomFilePtr = fopen("rooms.txt", "w");

    bool flag = false;

    //checking if file pointers are null
    if(patientFilePtr != NULL && roomFilePtr != NULL){
        flag = true;
    }// end if

    //Closes the files.
    fclose(patientFilePtr);
    fclose(roomFilePtr);

    return flag;
}// end function


//***************************************************************
//checks the string value.
//***************************************************************
bool NameEntered(const char *string){
    int choice;
    bool flag = true;

    if(strcmp(string, "patients") == 0){
        do {
            puts("\n\n");
            patientsOptions();// Displays the patient options
            scanf("%d", &choice);
            operationsP(&choice);// Patient operations
        }while (choice != 6);

    }else if(strcmp(string, "rooms") == 0){
        do {

            puts("\n\n");
            roomsOptions();// Displays the room options
            scanf("%d", &choice);
            operationsR(&choice);// Room operations
        }while(choice != 6);

    } else if(strcmp(string, "exit") == 0){
        flag = false;
    }else{
        puts("Error Invalid Input\n");
    }

    return flag;
}


//***************************************************************
// operations for the patient files.
//***************************************************************
void operationsP(const int *choice){

    switch(*choice){
        case 1:
            puts("\n\n");
            addPatient();// Adds patient to the file.
            break;

        case 2:
            //display patient report.
            displayPatients();
            break;

        case 3:
            //Updates the patient file.
            pFileUpdate();
            break;

        case 4:
            // automatically stores patient in available room
            aiStorePatientInRoom();
            break;

        case 5:
            //generates the Covid status report
            covidStatusReport();
            break;

        case 6:
            //goes back
            break;


        default:
            puts("Invalid input\n");
            break;
    }// end switch

}// end function


//***************************************************************
// operations for room file.
//***************************************************************
void operationsR(const int *choice){
    switch(*choice){
        case 1:
            puts("\n\n");
            //Adds empty room to room file.
            addEmptyRoom();
            break;

        case 2:
            puts("\n\n");
            //add rooms with patients.
            addRoomWithPatients();
            break;

        case 3:
            //Generate the room admittance age report.
            generateRoomAdmittanceAgeReport();
            break;

        case 6:
            //Goes back
            break;
        default:
            puts("Invalid input\n");
            break;
    }// end switch

}// end function

//***************************************************************
// Add patient
//***************************************************************
void addPatient(){
    //Declaring struct pointer.
    //This is the same thing as:  struct Patient patient;
    struct Patient *patient = (struct Patient*)calloc(1,sizeof(struct Patient));

    //Opening file in append mode.
    FILE *patientFile = fopen("patients.txt", "a");
    checkPtr(patient);

    patient = collectPatientInfo(patient);   //Collects patients information
    checkPtr(patient);

    //Storing data in file.
    fprintf(patientFile, "%ld\t %s\t %s\t %s\t %d\t %s\n",patient->patientID, patient->firstName,
            patient->lastName, patient->covidStatus, patient->birthYear, "admitted");
    puts("\n\npatient successfully added.");

fclose(patientFile);
free(patient);
}

//***************************************************************
//Collects patient information
//***************************************************************
struct Patient *collectPatientInfo(struct Patient *patient){
    int choice;
    //Generating Patient id
    patient->patientID = checkGeneratedPatientID();
    //Collecting the Name.
    printf("***************************************************");
    printf("\n* Enter Patient firstname: ");
    scanf("%s", patient->firstName);

    printf("* Enter Patient lastname: ");
    scanf("%s", patient->lastName);

    patientCovidStatusOptions();// Displaying covid options
    scanf("%d", &choice);
    patient->covidStatus =  patientCovidStatus(&choice); //returns the covid status.

    printf("* Enter patient birth year: ");
    scanf("%d", &patient->birthYear);
    //making sure the birth year is not 0
    if (patient->birthYear <= 0){
        puts("Invalid Birth year.\n");
        return NULL;
    }// end if


    return patient;
}


//***************************************************************
// generate the patient id
//***************************************************************
long int  checkGeneratedPatientID(){
    FILE *patientFile = fopen("patients.txt", "r");
    long int pID;
    int endOfFile, index = 1;
    char *line = (char*)malloc(1000 *sizeof(char));
    checkPtr(line);

    endOfFile  = fileLength(patientFile, line); //collects the number of patients in the file
    rewind(patientFile);//rewind the

    if(endOfFile == 0){
        fclose(patientFile);
        free(line);
        return 1000000;
    }

    //Gets the last it and add 1 to it.
    while(true){
        fgets(line, 500, patientFile);
        if( index == endOfFile && strcmp(line, "\n") != 0){
            pID = patientIDConverter(line) + 1;
            break;
        }
        if(strcmp(line, "\n") != 0 && strcmp(line, " ") != 0){
            index++;
        }
        memset(line, '\0', sizeof(*line));
    }

    fclose(patientFile);
    free(line);
return pID;
}


//***************************************************************
//  checks if the ptr has memory
//***************************************************************
void checkPtr(void *ptr){
    if(ptr == NULL){
        puts("Error memory was not allocated\n");
        exit(EXIT_FAILURE);
    }// end if
}


//***************************************************************
//  Puts the first 7 integers in another array then converts it to string
//***************************************************************
long int patientIDConverter(const char *ID){
    char *idLine = (char*)malloc(8*sizeof(char));

    checkPtr(idLine);
    int index;

    for(index=0; index<8; index++){
        idLine[index] = *(ID+index);
    }

    long int pID = atoi(idLine);// converts the new array to a  int.
    free(idLine);
    return pID;
}


//***************************************************************
// Returns the number of things within the file
//***************************************************************
int fileLength(FILE *ptr, char *line){
    int endOfFile = 0;

    while(fgets(line, 500, ptr)){
        if(strcmp(line, "\n") != 0 && strcmp(line, " ") != 0) {
            endOfFile++;
        }
    }
    return endOfFile;
}


//***************************************************************
// returns patient covid status during adding patient
//***************************************************************
char *patientCovidStatus(const int *ptr){
    char *string = NULL;
    switch (*ptr) {
        case 1:
            string = "None";
            break;

        case 2:
            string = "Mild";
            break;

        case 3:
            string = "Average";
            break;

        case 4:
            string = "Severe";
            break;

        case 5:
            string = "Critical";
            break;

        default:
            puts("Invalid input\n");
            break;
    }// end switch

    return string;
}

//***************************************************************
// Adds room without patient id
//***************************************************************
void addEmptyRoom(){
    //Declaring struct pointer.
    //This is the same thing as:  struct Patient patient;
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));

    //Opening file in append mode.
    FILE *roomFile = fopen("rooms.txt", "a");
    checkPtr(room);

    room = collectRoomInfo(room); // collects room information and returns it
    checkPtr(room);

    fprintf(roomFile, "%d\t %s\t %d\t %s\n",room->roomID, room->respiratorCheck,
            room->roomBeds, room->roomHelp);

    puts("Room was added\n");
    fclose(roomFile);
    free(room);
}


//***************************************************************
// Prompt user for value then collects it.
//***************************************************************
struct Room *collectRoomInfo(struct Room *room){
    int choice;

    //generate Room ID
    room->roomID = checkGeneratedRoomID();

    printf("\n* 1.Respirator \n* 2.None");
    printf("\n* >> ");
    scanf("%d", &choice);
    room->respiratorCheck =  roomResCheck(&choice); // checks that the inn put is valid

    printf("Enter the number of beds: ");
    scanf("%d", &room->roomBeds);

    //Checks that the number of beds are valid.
    if(room->roomBeds <= 0 || room->roomBeds > 5 ){
        puts("Invalid input\n");
        return NULL;
    }

    printf("\n* 1.Nurse \n* 2.Doctor \n* 3.None");
    printf("\n* >> ");
    scanf("%d", &choice);
    room->roomHelp = roomHelpCheck(&choice);// checks valid input.

    return room;
}

//***************************************************************
//generates room id
//***************************************************************
int checkGeneratedRoomID(){
    FILE *roomFile = fopen("rooms.txt", "r");
    int rID;
    int endOfFile, index = 1;
    char *line = (char*)malloc(1000 *sizeof(char));
    checkPtr(line);

    endOfFile  = fileLength(roomFile, line);
    rewind(roomFile);

    if(endOfFile == 0){
        fclose(roomFile);
        free(line);
        return 100;
    }

    //Gets the line from the room file find the latest id and add 1 to it
    while(true){
        fgets(line, 500, roomFile);
        if( index == endOfFile && strcmp(line, "\n") != 0){
            rID = roomIDConverter(line) + 1;
            break;
        }
        if(strcmp(line, "\n") != 0 && strcmp(line, " ") != 0){
            index++;
        }
        memset(line, '\0', sizeof(*line));
    }

    fclose(roomFile);
    free(line);
    return rID;
}


//***************************************************************
//Sharethia McCarthy - converts room id
//***************************************************************
int roomIDConverter(const char *ID){
    char *idLine = (char*)malloc(4*sizeof(char));
    checkPtr(idLine);
    int index;

    for(index=0; index<4; index++){
        idLine[index] = *(ID+index);
    }

    int rID = atoi(idLine); // atio converts a string to a integer.
    free(idLine);
    return rID;
}


//***************************************************************
//check the user value to make sure that it is one of the following.
//***************************************************************
char *roomResCheck(const int *ptr) {
    char *string = NULL;
    switch (*ptr) {
        case 1:
            string = "Respirator";
            break;

        case 2:
            string = "Mild";
            break;

        default:
            puts("Invalid input\n");
            break;
    }
    return string;
}


//***************************************************************
///check the user value to make sure that it is one of the following.
//***************************************************************
char *roomHelpCheck(const int *ptr) {
    char *string = NULL;
    switch (*ptr) {
        case 1:
            string = "Nurse";
            break;

        case 2:
            string = "Doctor";
            break;

        case 3:
            string = "None";
            break;

        default:
            puts("Invalid input\n");
            break;
    }
    return  string;
}


//***************************************************************
//Adds a patient to an existing room.
//***************************************************************
void addRoomWithPatients(){
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));
    room->roomHelp = (char*)malloc(100 *sizeof(char));
    room->respiratorCheck = (char*)malloc(100 *sizeof(char));
    struct Patient *patient = (struct Patient*)calloc(1,sizeof(struct Patient));
    patient->covidStatus = (char*)malloc(100 *sizeof(char));
    char *line = (char*)malloc(1000 *sizeof(char));


    FILE *roomFile = fopen("rooms.txt", "r+");
    FILE *roomTempFile = fopen("roomTemp.txt", "w+");
    FILE *patientFile = fopen("patients.txt", "r+");
    int lineToDel, count = 0;
    int indexValidId, secondIndex;
    bool flag = false;


    checkPtr(room);
    checkPtr(line);
    checkPtr(room->respiratorCheck);
    checkPtr( room->roomHelp);
    checkPtr(patient);
    checkPtr(patient->covidStatus);

    printf("Enter the room ID: ");
    scanf("%d", &room->roomID);
    //check if valid
    if(!checkRoomID(&room->roomID)){
        puts("Invalid Id\n");
        fclose(roomFile);
        fclose(roomTempFile);
        fclose(patientFile);
        remove("roomTemp.txt");
        return;
    }

    printf("Enter the patient ID: ");
    scanf("%ld", &patient->patientID);

    //check if valid
    if(!checkPatientId(&patient->patientID)){
        puts("Invalid Id\n");
        fclose(roomFile);
        fclose(roomTempFile);
        fclose(patientFile);
        remove("roomTemp.txt");
        return;
    }

    //Takes the patient we want from the patient file.
    while(true){
        fgets(line, 500, patientFile);
        if(strcmp(line, "\n") != 0){
            if(patientIDConverter(line) == patient->patientID) {
                patient = splintPatientLine(line);
                break;
            }

        }
        memset(line, '\0', sizeof(*line));
    }

    //Goes into the room file find the avaliable room
    // if there is one we take out the line uptade it and re store everything in a temp file.
    while (!feof(roomFile)) {
        memset(line, '\0', sizeof(*line));
        fgets(line, 500, roomFile);
        if (roomIDConverter(line) == room->roomID) {
            room = splintRoomLine(line);
            flag = roomWithBedCheck(room);
            if (flag) {
                rewind(roomFile);
                count = 0;
                lineToDel = getDeleRoomLine(&room->roomID);
                while (!feof(roomFile)) {
                    strcpy(line, "\0");
                    fgets(line, 500, roomFile);
                    if (!feof(roomFile)) {
                        count++;
                        if (count != lineToDel) {
                            fprintf(roomTempFile, "%s", line);
                        } else if (count == lineToDel) {
                            fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                    room->roomBeds, room->roomHelp);
                            for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                if (checkPatientId(&room->patientIDS[indexValidId])) {
                                    fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                }
                            }
                            fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                        }
                    }
                }
                break;
            }

        }
    }

    puts("Patient was added to room\n");

    //close the files as well as renaming them
    fclose(roomFile);
    fclose(roomTempFile);
    fclose(patientFile);
    free(room);
    free(line);
    free(patient);
    remove("rooms.txt");
    rename("roomTemp.txt", "rooms.txt");
}


//***************************************************************
//Checks if room id is valid
//***************************************************************
bool checkRoomID(const int *ptr){
    //Opening file in read mode.
    FILE *roomFile = fopen("rooms.txt", "r");
    bool flag = false;
    int endOfFile, index = 1;
    char *line = (char*)malloc(1000 *sizeof(char));
    checkPtr(line);

    endOfFile  = fileLength(roomFile, line);
    rewind(roomFile);

    //opens the room file and check if the id is present.
    while(true){
        fgets(line, 300, roomFile);
        if(strcmp(line, "\n") != 0){
            if(roomIDConverter(line) == *ptr) {
                flag = true;
                break;
            }

        }
        if(strcmp(line, "\n") != 0 && strcmp(line, " ") != 0){
            index++;
        }
        memset(line, '\0', sizeof(*line));
    }

    fclose(roomFile);
    free(line);
    return flag;
}


//***************************************************************
// Updates patient file or Discharge patient.
//***************************************************************
void pFileUpdate(){
    int choice;

    puts("\n*1.Change COVID STATUS \n*2.discharge patient");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            changePatientStatus(); // changes the patient covid status.
            break;

        case 2:
            deletePatient(); // deletes the patient
            break;

        default:
            break;
    }

}


//***************************************************************
// Sharethia McCarthy - deletes patients from file as well as discharge them if they are in a room
//***************************************************************
void deletePatient() {

    struct Patient *patient = (struct Patient *) calloc(1, sizeof(struct Patient)); //Allocating memory.
    struct Room *room = (struct Room *) calloc(1, sizeof(struct Room));
    room->respiratorCheck = (char *) malloc(100 * sizeof(char));
    room->roomHelp = (char *) malloc(100 * sizeof(char));
    long int lineToDel, count = 0;
    int roomLineToDel;
    char *line = (char *) malloc(1000 * sizeof(char));
    bool flag = false;
    int mainIndex;


    //Checking if pointers are valid.
    checkPtr(line);
    checkPtr(room);
    checkPtr(room->roomHelp);
    checkPtr(room->respiratorCheck);

    //Opening file in append mode.
    FILE *patientFile = fopen("patients.txt", "r+");
    FILE *pTempFile = fopen("temp.txt", "w");
    FILE *roomFile = fopen("rooms.txt", "r+");
    FILE *roomTempFile = fopen("roomTemps.txt", "w");


    //Checking if pointers are valid.
    checkPtr(patient);
    checkPtr(pTempFile);

    printf("Enter the patient ID: ");
    scanf("%ld", &patient->patientID);

    //check if valid
    if (!checkPatientId(&patient->patientID)) {
        puts("Invalid Id\n");
        fclose(patientFile);
        fclose(pTempFile);
        fclose(roomTempFile);
        fclose(roomFile);
        remove("temp.txt");
        remove("roomTemps.txt");
        return;
    }
    lineToDel = getDelePatientLine(&patient->patientID); // get patient line to delete
    //prints the patient file except the patient we want to remove.
    while (!feof(patientFile)) {
        strcpy(line, "\0"); // put null values '\0' in line
        fgets(line, 500, patientFile);
        if (!feof(patientFile)) {
            count++;
            if (count != lineToDel) {
                fprintf(pTempFile, "%s", line);
            }
        }
    }
    puts("Patient was discharged.\n");
    count = 0;
    //this opens the room file file checks it the patient we are discharging is in a room
    // if it is we remove it and reprint it in a temp file which will be renamed.
    if (!checkRoomForPatient(&patient->patientID)) { // if patient we are deleting is in a room it returns true.
        flag = true;
        room->roomID = getRoomIDToDelPatient(&patient->patientID);
        roomLineToDel = getDeleRoomLine(&room->roomID); // gets the line to edit
        while (!feof(roomFile)) {
            memset(line, '\0', 1000);
            fgets(line, 500, roomFile);
            room = splintRoomLine(line);
            if (!feof(roomFile)) {
                count++;
                if (count != roomLineToDel) {
                    fprintf(roomTempFile, "%s", line);
                } else if (count == roomLineToDel) {
                    fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck, room->roomBeds,
                            room->roomHelp);
                    for (mainIndex = 0; mainIndex < room->roomBeds; mainIndex++) {
                        if (patient->patientID != room->patientIDS[mainIndex]) {
                            if (checkPatientId(&room->patientIDS[mainIndex]) && room->patientIDS[mainIndex] != 0) {
                                fprintf(roomTempFile, "%ld\t", room->patientIDS[mainIndex]);
                            }
                        }
                    }
                    fprintf(roomTempFile, "\n");
                }
            }
        }

    }

    fclose(patientFile);
    fclose(pTempFile);
    fclose(roomTempFile);
    fclose(roomFile);
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (!flag) {
        remove("roomTemps.txt");
    }


    if (flag) {
        if (remove("rooms.txt") != 0){
            fprintf(stderr, "Error deleting the file rooms: %s\n", strerror(errno));
        }

        if (rename("roomTemps.txt", "rooms.txt") != 0) {
            fprintf(stderr, "Error renaming file: %s\n", strerror(errno));
        }
        }
    free(patient);
    free(room);
    free(line);
    }


//***************************************************************
// Makes sure that the id that was entered by the user is valid
//***************************************************************
    bool checkPatientId(const long int *ptr) {
        //Opening file in read mode.
        FILE *patientFile = fopen("patients.txt", "r");
        bool flag = false;

        char *line = (char *) malloc(1000 * sizeof(char));
        checkPtr(line);

        rewind(patientFile);

        while (true) {
            fgets(line, 500, patientFile);
            if (strcmp(line, "\n") != 0) {

                if (patientIDConverter(line) == *ptr && !feof(patientFile)) {
                    flag = true;
                    break;
                }
                if (feof(patientFile)) {
                    break;
                }
            }
            memset(line, '\0', sizeof(*line));
        }

        fclose(patientFile);
        free(line);
        return flag;
    }


//***************************************************************
//Jhavon Brown - gets the position of the patient we want to delete
//***************************************************************
int getDelePatientLine(const long int *ptr) {
//Opening file in read mode.
        FILE *patientFile = fopen("patients.txt", "r");

         int lineCount = 0;
        char *line = (char *) malloc(1000 * sizeof(char));
        checkPtr(line);

        rewind(patientFile);//rewind the file pointer

        //Loops through the file check the patient id  if not equal to what the user entered add one to lineCount.
        while (true) {
            fgets(line, 500, patientFile);
            if (strcmp(line, "\n") != 0) {
                if (patientIDConverter(line) == *ptr) {
                    lineCount++;
                    break;
                }

            }
            if (strcmp(line, "\n") != 0 && strcmp(line, " ") != 0) {
                lineCount++;
            }
            memset(line, '\0', 1000);// places 10000 null characters in line.
        }

        fclose(patientFile);
        free(line); // free memory
        return lineCount;
    }


//***************************************************************
// Jhavon Brown - This function changes the patient covid status
//***************************************************************
    void changePatientStatus() {

        struct Patient *patient = (struct Patient *) calloc(1, sizeof(struct Patient));// allocate memory to the variable
        int choice;
        long int lineToDel, count = 0;
        char *line = (char *) malloc(1000 * sizeof(char));
        patient->covidStatus = (char *) malloc(100 * sizeof(char));
        char *newCovidS = NULL;


        FILE *pTempFile = fopen("temp.txt", "w");
        checkPtr(pTempFile);// check the pointer and make sure it is not NULL

        FILE *patientFile = fopen("patients.txt", "r+");
        checkPtr(line);
        checkPtr(patient);
        checkPtr(patient->covidStatus);

        printf("Enter the patient ID: ");
        scanf("%ld", &patient->patientID);
        //check if valid
        if (!checkPatientId(&patient->patientID)) {
            puts("Invalid Id\n");
            fclose(patientFile);
            fclose(pTempFile);
            remove("temp.txt");
            return;
        }

        patientCovidStatusOptions();
        scanf("%d", &choice);
        newCovidS = patientCovidStatus(&choice);
        checkPtr(newCovidS);


        //loop patient file find the patient to edit via the id
        while (true) {
            fgets(line, 500, patientFile);
            if (strcmp(line, "\n") != 0) {
                if (patientIDConverter(line) == patient->patientID) {
                    patient = splintPatientLine(line);
                    break;
                }

            }
            memset(line, '\0', 1000);// empty the line
        }

        rewind(patientFile);// rewind the file
        memset(line, '\0', 1000);


        //Prints everything in the temp file including the new patient information.
        lineToDel = getDelePatientLine(&patient->patientID);
        while (!feof(patientFile)) {
            strcpy(line, "\0");
            fgets(line, 500, patientFile);
            if (!feof(patientFile)) {
                count++;
                if (count != lineToDel) {
                    fprintf(pTempFile, "%s", line);
                } else if (count == lineToDel) {
                    //Storing data in file.
                    fprintf(pTempFile, "%ld\t %s\t %s\t %s\t %d\t %s\n", patient->patientID, patient->firstName,
                            patient->lastName, newCovidS, patient->birthYear, "admitted");
                    puts("COVID Status Changed.");
                }
            }
        }
//
        fclose(patientFile);
        fclose(pTempFile);

        if (remove("patients.txt") != 0) {
            fprintf(stderr, "Error deleting the file rooms: %s\n", strerror(errno));
        }
        if (rename("temp.txt", "patients.txt") != 0) {
            fprintf(stderr, "Error renaming file: %s\n", strerror(errno));
        }

        free(patient); // free memory that  was allocated to the pointer.
        free(line);
        free(newCovidS);

    }


//***************************************************************
// passes the line from fgets to be seperated.
//***************************************************************
    struct Patient *splintPatientLine(const char *line) {
//    int lineToDel, count = 0;
        struct Patient *patient = (struct Patient *) calloc(1, sizeof(struct Patient));
        patient->covidStatus = (char *) malloc(100 * sizeof(char));

        checkPtr(patient);
        checkPtr(patient->covidStatus);

        FILE *patientTempFile = fopen("patientTemp.txt", "w+");
        checkPtr(patientTempFile);

        fprintf(patientTempFile, "%s", line);

        rewind(patientTempFile);
        fscanf(patientTempFile, "%ld %s %s %s %d %s", &patient->patientID, patient->firstName, patient->lastName,
               patient->covidStatus, &patient->birthYear, patient->adDis);


        fclose(patientTempFile);
        remove("patientTemp.txt");
        return patient;
    }

//***************************************************************
//atomatically stores patient in a avalable room.
//***************************************************************
    void aiStorePatientInRoom() {
        struct Room *room = (struct Room *) calloc(1, sizeof(struct Room));
        char *line = (char *) malloc(1000 * sizeof(char));
        room->respiratorCheck = (char *) malloc(1000 * sizeof(char));
        room->roomHelp = (char *) malloc(1000 * sizeof(char));
        struct Patient *patient = (struct Patient *) calloc(1, sizeof(struct Patient));
        patient->covidStatus = (char *) malloc(100 * sizeof(char));
        int lineToDel, count = 0;
        int year = 2021, patientAge, indexValidId, secondIndex;
        bool flag = false;
        bool aiDel = false;

        //Opening file in append mode.
        FILE *roomFile = fopen("rooms.txt", "r+");
        FILE *roomTempFile = fopen("roomTemp.txt", "w+");
        FILE *patientFile = fopen("patients.txt", "r+");

        FILE *pTempFile = fopen("temp.txt", "w+");
        checkPtr(pTempFile);

        checkPtr(room);
        checkPtr(line);
        checkPtr(room->respiratorCheck);
        checkPtr(room->roomHelp);
        checkPtr(patient);
        checkPtr(patient->covidStatus);

        printf("Enter the patient ID: ");
        scanf("%ld", &patient->patientID);

        //check if valid
        if (!checkPatientId(&patient->patientID)) {
            puts("Invalid Id\n");
            fclose(roomTempFile);
            fclose(pTempFile);
            remove("roomTemp.txt");
            remove("temp.txt");
            return;
        }

        if (!checkRoomForPatient(&patient->patientID)) {
            puts("Patient already in a room\n");
            fclose(roomTempFile);
            fclose(pTempFile);
            remove("roomTemp.txt");
            remove("temp.txt");
            return;
        }

        while (true) {
            fgets(line, 500, patientFile);
            if (strcmp(line, "\n") != 0) {
                if (patientIDConverter(line) == patient->patientID) {
                    patient = splintPatientLine(line);
                    break;
                }

            }
            memset(line, '\0', sizeof(*line));
        }

        patientAge = year - patient->birthYear;

        if (strcmp(patient->covidStatus, "Critical") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = criticalRoomCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }
        } else if (strcmp(patient->covidStatus, "Severe") == 0 && patientAge >= 60) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = severeRoomCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }
        } else if (strcmp(patient->covidStatus, "Mild") == 0 || strcmp(patient->covidStatus, "Average") == 0 &&
        patientAge >= 60) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }

        } else if (patientAge >= 40 && patientAge <= 60 && strcmp(patient->covidStatus, "Severe") == 0 ||
                   strcmp(patient->covidStatus, "Average") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }

        } else if (patientAge >= 40 && patientAge <= 60 && strcmp(patient->covidStatus, "Mild") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }
        } else if (patientAge >= 20 && patientAge <= 39 && strcmp(patient->covidStatus, "Severe") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedDoctorCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }
        } else if (patientAge >= 20 && patientAge <= 39 && strcmp(patient->covidStatus, "Mild") == 0 ||
                   strcmp(patient->covidStatus, "Average") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }

        } else if (patientAge < 20 && strcmp(patient->covidStatus, "Severe") == 0 ||
                   strcmp(patient->covidStatus, "Average") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedNurseCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }

            }

        } else if (patientAge < 20 && strcmp(patient->covidStatus, "Mild") == 0) {
            while (!feof(roomFile)) {
                memset(line, '\0', sizeof(*line));
                fgets(line, 500, roomFile);
                room = splintRoomLine(line);
                flag = roomWithBedCheck(room);
                if (flag) {
                    rewind(roomFile);
                    count = 0;
                    lineToDel = getDeleRoomLine(&room->roomID);
                    while (!feof(roomFile)) {
                        strcpy(line, "\0");
                        fgets(line, 500, roomFile);
                        if (!feof(roomFile)) {
                            count++;
                            if (count != lineToDel) {
                                fprintf(roomTempFile, "%s", line);
                            } else if (count == lineToDel) {
                                fprintf(roomTempFile, "%d\t %s\t %d\t %s\t", room->roomID, room->respiratorCheck,
                                        room->roomBeds, room->roomHelp);
                                for (indexValidId = 0; indexValidId < room->roomBeds - 1; indexValidId++) {
                                    if (checkPatientId(&room->patientIDS[indexValidId])) {
                                        fprintf(roomTempFile, "\t%ld\t", room->patientIDS[indexValidId]);
                                    }
                                }
                                fprintf(roomTempFile, "\t%ld\n", patient->patientID);
                            }
                        }
                    }
                    break;
                }
            }
        } else if (strcmp(patient->covidStatus, "None") == 0) {
            aiDeletePatient(patientFile, pTempFile, &patient->patientID);
            aiDel = true;
        }
        puts("Patient added to room\n");
        fclose(roomFile);
        fclose(roomTempFile);
        fclose(patientFile);
        fclose(pTempFile);
        free(room);
        free(line);
        free(patient);

        if (!aiDel) {

            if( remove("rooms.txt") != 0){
                fprintf(stderr, "Error deleting room file: %s\n", strerror(errno));
            }
            if(remove("temp.txt") != 0){
                fprintf(stderr, "Error deleting temp file: %s\n", strerror(errno));
            }
            rename("roomTemp.txt", "rooms.txt");
        }

        if (aiDel) {
            if(  remove("patients.txt") != 0){
                fprintf(stderr, "Error deleting patient file: %s\n", strerror(errno));
            }
            if(remove("roomTemp.txt") != 0){
                fprintf(stderr, "Error deleting roomTemp file: %s\n", strerror(errno));
            }

            rename("temp.txt", "patients.txt");

        }
    }


//***************************************************************
// Sharethia McCarthy - return the line we want to edit
//***************************************************************
int getDeleRoomLine(const int *ptr){
    //Opening file in read mode.
    FILE *roomFile = fopen("rooms.txt", "r");

    long int lineCount = 0;
    char *line = (char*)malloc(1000 *sizeof(char));
    checkPtr(line);

    rewind(roomFile);

    while(!feof(roomFile)){
        fgets(line, 500, roomFile);
        if(strcmp(line, "\n") != 0){
            if(roomIDConverter(line) == *ptr) {
                lineCount++;
                break;
            }

        }
        if(strcmp(line, "\n") != 0 && strcmp(line, " ") != 0){
            lineCount++;
        }
        memset(line, '\0', sizeof(*line));
    }

    fclose(roomFile);
    free(line);
    return lineCount;
}


//***************************************************************
//  Collects the data and place it in room and returns it.
//***************************************************************
struct Room *splintRoomLine(const char *line){
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));
    room->respiratorCheck  = (char*)malloc(100 *sizeof(char));
    room->roomHelp  = (char*)malloc(100 *sizeof(char));

    checkPtr(room);
    checkPtr(room->roomHelp);
    checkPtr(room->respiratorCheck);

    FILE *roomTempFile = fopen("roomTemp.txt", "w+");
    checkPtr(roomTempFile);

    fprintf(roomTempFile, "%s", line);

    rewind(roomTempFile);
    fscanf(roomTempFile, "%d %s %d %s %ld %ld %ld %ld %ld", &room->roomID, room->respiratorCheck, &room->roomBeds, room->roomHelp,
            &room->patientIDS[0], &room->patientIDS[1], &room->patientIDS[2], &room->patientIDS[2],
            &room->patientIDS[4]);

//    fclose(patientFile);
    fclose(roomTempFile);
    remove("roomTemp.txt");
    return room;
}


//***************************************************************
//checks for a critical room
//***************************************************************
bool criticalRoomCheck(struct Room *room){
    bool flag = true;
    int index, counter=0;

    for(index=0; index<room->roomBeds; index++){
        long int pID = room->patientIDS[index];
        if(checkPatientId(&pID)){
            counter++;
        }
    }
    if(counter == room->roomBeds || strcmp(room->respiratorCheck, "Respirator") != 0 &&
    strcmp(room->roomHelp, "Doctor") != 0){
        return false;
    }

    return flag;
}

//***************************************************************
//checks for a sever room
//***************************************************************
bool severeRoomCheck(struct Room *room){
    bool flag = true;
    int index, counter=0;

    for(index=0; index<room->roomBeds; index++){
        long int pID = room->patientIDS[index];
        if(checkPatientId(&pID)){
            counter++;
        }
    }
    if(counter == room->roomBeds || strcmp(room->respiratorCheck, "Respirator") != 0 ||
       strcmp(room->roomHelp, "Nurse") != 0){
        return false;
    }

    return flag;
}

//***************************************************************
//checks for a room with beds
//***************************************************************
bool roomWithBedCheck(struct Room *room){
    bool flag = true;
    int index, counter=0;

    for(index=0; index<room->roomBeds; index++){
        long int pID = room->patientIDS[index];
        if(checkPatientId(&pID)){
            counter++;
        }
    }
    if(counter == room->roomBeds){
        return false;
    }

    return flag;
}

//***************************************************************
//checks for a room with a nurse beds
//***************************************************************
bool roomWithBedNurseCheck(struct Room *room){
    bool flag = true;
    int index, counter=0;

    for(index=0; index<room->roomBeds; index++){
        long int pID = room->patientIDS[index];
        if(checkPatientId(&pID)){
            counter++;
        }
    }
    if(counter == room->roomBeds && strcmp(room->roomHelp, "Nurse") != 0){
        return false;
    }

    return flag;
}

//***************************************************************
//checks for a room with a doctor beds
//***************************************************************
bool roomWithBedDoctorCheck(struct Room *room){
    bool flag = true;
    int index, counter=0;

    for(index=0; index<room->roomBeds; index++){
        long int pID = room->patientIDS[index];
        if(checkPatientId(&pID)){
            counter++;
        }
    }
    if(counter == room->roomBeds && strcmp(room->roomHelp, "Doctor") != 0){
        return false;
    }

    return flag;
}


//***************************************************************
//Grosjean Jackson - printing all patients in the file.
//***************************************************************
void displayPatients()
{
    puts("\n\n");
    FILE *patientFile = fopen("patients.txt", "r");
    char *line = (char*)malloc(1000 *sizeof(char));

    checkPtr(line);

    //gets each line from file and print it out
    while (fgets(line, 500, patientFile)) {
        printf("%s", line);
    }

    fclose(patientFile);
    free(line);
}


//***************************************************************
//Jhavon Brown - finds all patients in the room and find there age
//***************************************************************
void generateRoomAdmittanceAgeReport(){

    int overSixties = 0, betweenFortyAndSixty = 0, betweenTwentyAndThirtyNine = 0, lessThanTwenty = 0, mainIndex;
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));
    char *line = (char*)malloc(1000 *sizeof(char));
    char *pLine = (char*)malloc(1000 *sizeof(char));
    room->respiratorCheck = (char*)malloc(1000 *sizeof(char));
    room->roomHelp = (char*)malloc(1000 *sizeof(char));
    struct Patient *patient = (struct Patient*)calloc(1,sizeof(struct Patient));

    int lineToDel, count = 0, choice;
    int year = 2021, patientAge, indexValidId, secondIndex;
    bool flag = false;
    //60s, 40 to 60, 20 to 39 and younger than 39
    FILE *roomFile = fopen("rooms.txt", "r");
    FILE *patientFile = fopen("patients.txt", "r");

    checkPtr(room);
    checkPtr(line);
    checkPtr(room->respiratorCheck);
    checkPtr( room->roomHelp);
    checkPtr(patient);
    checkPtr(pLine);

    while (!feof(roomFile)) {
        memset(line, '\0', sizeof(*line));
        memset(pLine, '\0', sizeof(*pLine));
        rewind(patientFile);
        fgets(line, 500, roomFile);
        room = splintRoomLine(line);
        for(mainIndex=0; mainIndex<room->roomBeds; mainIndex++){
            if(checkPatientId(&room->patientIDS[mainIndex])){
                rewind(patientFile);
                while(true){
                    fgets(pLine, 500, patientFile);
                    if(strcmp(pLine, "\n") != 0){
                        if(patientIDConverter(pLine) == room->patientIDS[mainIndex]) {
                            patient = splintPatientLine(pLine);
                            break;
                        }

                    }
                    memset(pLine, '\0', sizeof(*pLine));
                }
                patientAge =  year - patient->birthYear;
                if(patientAge > 60){
                    overSixties++;
                 } else if(patientAge >=40 && patientAge<=60){
                        betweenFortyAndSixty++;
                 }else if(patientAge >=20 && patientAge <=39){
                        betweenTwentyAndThirtyNine++;
                }else if(patientAge <20){
                    lessThanTwenty++;
            }
            }
        }

    }

    puts("--The Reports Of Patients in rooms grouped by age--\n");
    printf("The number of Patients over 60: %d\n", overSixties);
    printf("The number of Patients between 40 and 60: %d\n", betweenFortyAndSixty);
    printf("The number of Patients between 20 and 39: %d\n", betweenTwentyAndThirtyNine);
    printf("The number of Patients less than 20: %d\n", lessThanTwenty);

//    The user should then be given the option to save the report to a file
//    (the system will request a file name from the user to save the file).

    puts("Do you want to save data to file 1 for yes 2 for no\n");
    scanf("%d", &choice);
    saveRoomAdmittanceAgeReport(&overSixties, &betweenFortyAndSixty, &betweenTwentyAndThirtyNine,
                                &lessThanTwenty, &choice);


    fclose(roomFile);
    fclose(patientFile);
    free(room);
    free(line);
    free(pLine);
    free(patient);
}


//***************************************************************
//Jhavon Brown - saves or do not save the patient report
//***************************************************************
void saveRoomAdmittanceAgeReport(const int *ptrOne, const int *ptrTwo, const int *ptrThree,
                                 const int *ptrFour, const int* choice){

    FILE *reportFile = NULL;
    char *fileName = (char*)malloc(1000 *sizeof(char));
    checkPtr(fileName);

    switch(*choice){
        case 1:
            puts("Enter the name you want to give to the file no spaces format eg ROOM_REPORT: ");
            scanf("%s", fileName);
            reportFile = fopen(strcat(fileName, ".txt"), "w+");
            checkPtr(reportFile);
            fprintf(reportFile, "Over 60: %d\n", *ptrOne);
            fprintf(reportFile, "Between 40 and 60: %d\n", *ptrTwo);
            fprintf(reportFile, "Between 20 and 39: %d\n", *ptrThree);
            fprintf(reportFile, "Less than 20: %d\n", *ptrFour);
            break;

        case 2:
            break;

        default:
            puts("Invalid input\n");
            break;
    }
fclose(reportFile);
    free(fileName);
}

//***************************************************************
//Grosjean Jackson - checks the amount of patients with a Covid status.
//***************************************************************
void covidStatusReport(){
    //declare the variables.
    int none= 0, mild = 0, avg = 0, crt = 0, sev = 0, mainIndex;


    char *line = (char*)malloc(1000 *sizeof(char));// allocating memory to variables
    struct Patient *patient = (struct Patient*)calloc(1,sizeof(struct Patient)); // allocating memory to variables
    patient->covidStatus = (char*)malloc(1000 *sizeof(char));// allocating memory to variables

    int choice;
    bool flag = false;


    checkPtr(line); // this function checks that the pointer is not null.
    checkPtr(patient);
    checkPtr(patient->covidStatus);

    FILE *patientFile = fopen("patients.txt", "r");

    // going in the file line by line checking each patient covid status
    //depending on the status it add one to the counter.
    while (!feof(patientFile)) {
        memset(line, '\0', sizeof(*line));
        fgets(line, 500, patientFile);
        patient = splintPatientLine(line);

        if(strcmp(patient->covidStatus, "None") == 0){
            none++;
        } else if(strcmp(patient->covidStatus, "Mild") == 0){
            mild++;
        }else if(strcmp(patient->covidStatus, "Severe") == 0){
            sev++;
        }else if(strcmp(patient->covidStatus, "Critical") == 0){
            crt++;
        }else if(strcmp(patient->covidStatus, "Average") == 0){
            avg++;
        }

    }

    // Print the totals and ask user to save the file.
    puts("--The COVID reports--\n");
    printf("The number of Patients with no status: %d\n", none);
    printf("The number of Patients with a mild covid status: %d\n", mild);
    printf("The number of Patients with a severe covid status: %d\n", sev);
    printf("The number of Patients with a critical covid status: %d\n", crt);
    printf("The number of Patients with a average covid status: %d\n", avg);

    puts("\nDo you want to save data to file 1 for yes 2 for no\n");
    scanf("%d", &choice);

    // checks user input to save file our not.
    saveCovidReport(&none, &mild, &sev, &crt, &avg, &choice);

    fclose(patientFile);
    free(line);
    free(patient);
}

//***************************************************************
//Grosjean Jackson - checks the user input and save the file if it was one
//***************************************************************
void saveCovidReport(const int *ptrOne, const int *ptrTwo, const int *ptrThree,
                                 const int *ptrFour, const int *ptrFive, const int* choice){

    FILE *reportFile = NULL;
    char *fileName = (char*)malloc(1000 *sizeof(char));
    checkPtr(fileName);

    switch(*choice){
        case 1:
            puts("Enter the name you want to give to the file No Spaces eg format Covid_Report: ");
            scanf("%s", fileName);
            // saves data to file.
            reportFile = fopen(strcat(fileName, ".txt"), "w+");// strcat adds string 2 to string one
            checkPtr(reportFile);
            fprintf(reportFile, "The number of Patients with no status: %d\n", *ptrOne);
            fprintf(reportFile, "The number of Patients with a mild covid status: %d\n", *ptrTwo);
            fprintf(reportFile, "The number of Patients with a severe covid status: %d\n", *ptrThree);
            fprintf(reportFile, "The number of Patients with a critical covid status: %d\n", *ptrFour);
            fprintf(reportFile, "The number of Patients with a average covid status: %d\n", *ptrFive);

            break;

        case 2:
            break;

        default:
            puts("Invalid input\n");
            break;
    }
    fclose(reportFile);//closes file
    free(fileName);// free the memory that was allocated.
}

//***************************************************************
// discharg patient if covid status it none
//***************************************************************
void aiDeletePatient( FILE *filePtr, FILE *tempFile, const long int *ptr){
//    struct Patient *patient = (struct Patient*)calloc(1,sizeof(struct Patient));
    long int lineToDel, count = 0;

    char *line = (char*)malloc(1000 *sizeof(char));
    checkPtr(line);


rewind(filePtr);

    lineToDel = getDelePatientLine(ptr);
    while (!feof(filePtr)){
        strcpy(line, "\0");
        fgets(line, 500, filePtr);
        if(!feof(filePtr)){
            count++;
            if (count != lineToDel){
                fprintf(tempFile, "%s", line);
            }
        }
    }

    free(line);
}


//***************************************************************
// Sharethia McCarthy - checks room for patient id
//***************************************************************
bool checkRoomForPatient(const long int *ptr){
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));
    room->respiratorCheck  = (char*)malloc(100 *sizeof(char));
    room->roomHelp  = (char*)malloc(100 *sizeof(char));
    char *line = (char*)malloc(1000 *sizeof(char));
    int mainIndex;

    checkPtr(room);
    checkPtr(room->roomHelp);
    checkPtr(room->respiratorCheck);
    checkPtr(line);

    FILE *roomFile = fopen("rooms.txt", "r");
//    rewind(roomFile);

    // checks if the room has a valid patient id
    while(!feof(roomFile)){

        memset(line, '\0', 1000);
        fgets(line, 500, roomFile);// gets a line from the file
        room = splintRoomLine(line); // split the line
        for(mainIndex=0; mainIndex<room->roomBeds; mainIndex++){
            int temp = room->patientIDS[mainIndex];
            if(*ptr == temp) {
                fclose(roomFile);
                free(room);
                free(line);
                return false;
            }
            }
        }


    fclose(roomFile);
    free(room);
    free(line);
    return true;
}


//***************************************************************
//clears the screen
//***************************************************************
void sysClearScreen(){
    int index;
    for(index=0; index<10; index++){
        puts("\n\n\n\n\n\n\n\n");
    }
}

//***************************************************************
//Sharethia McCarthy - returns the room ID we want to edit
//***************************************************************
int getRoomIDToDelPatient(const long int *ptr){
    struct Room *room = (struct Room*)calloc(1,sizeof(struct Room));
    room->respiratorCheck  = (char*)malloc(100 *sizeof(char));
    room->roomHelp  = (char*)malloc(100 *sizeof(char));
    char *line = (char*)malloc(1000 *sizeof(char));
    int mainIndex , roomID;

    checkPtr(room);
    checkPtr(room->roomHelp);
    checkPtr(room->respiratorCheck);
    checkPtr(line);

    FILE *roomFile = fopen("rooms.txt", "r");
    rewind(roomFile);

    //gets the room if that we want to edit.
    while(!feof(roomFile)){
        memset(line, '\0', 1000);
        fgets(line, 500, roomFile);
        room = splintRoomLine(line);
        for(mainIndex=0; mainIndex<room->roomBeds; mainIndex++){
            if(*ptr == room->patientIDS[mainIndex]){
                roomID = room->roomID;
                fclose(roomFile);
                free(room);
                free(line);
                return roomID;
            }
        }
    }

    fclose(roomFile);
    free(room);
    free(line);
    return 0;
}

