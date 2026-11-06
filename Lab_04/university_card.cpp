// Operating Systems Lab - Lab Task 04: Implementation of system calls
// Stores university card details in a file and reads them back
// using Linux file-handling system calls: open(), write(), read(), close().

#include <iostream>     // cout / cerr for terminal output
#include <cstring>      // strlen(), strerror()
#include <cerrno>       // errno
#include <fcntl.h>      // open() and flags (O_WRONLY, O_CREAT, O_TRUNC, O_RDONLY)
#include <unistd.h>     // write(), read(), close()
#include <sys/stat.h>   // permission constants (S_IRUSR, S_IWUSR ...)

using namespace std;
int main() {
    const char *filename = "university_card.txt";

    // Card details (edit these if needed)
    const char *card =
        "Student Name: Misbah\n"
        "Registration Number: 2025-SE-10\n"
        "Department: Software Engineering\n"
        "Degree Program: BS Software Engineering\n"
        "University Name: University of Azad Jammu and Kashmir, Muzaffarabad\n";

    // ---------- STEP 1: Open file for writing ----------
    cout << "Writing University Card Details..." << endl;

    // O_WRONLY = write only, O_CREAT = create if missing,
    // O_TRUNC  = clear old contents, 0644 = rw-r--r-- permissions
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // ---------- STEP 2: Check whether open() succeeded ----------
    if (fd == -1) {
        cerr << "Error: could not open file for writing: " << strerror(errno) << endl;
        return 1;   // terminate program
    }

    // ---------- STEP 3: Write details using write() ----------
    ssize_t written = write(fd, card, strlen(card));
    if (written == -1) {
        cerr << "Error: write failed: " << strerror(errno) << endl;
        close(fd);
        return 1;
    }

    // ---------- STEP 4: Close the file after writing ----------
    if (close(fd) == -1) {
        cerr << "Error: close failed: " << strerror(errno) << endl;
        return 1;
    }
    cout << "University card details written successfully." << endl << endl;

    // ---------- STEP 5: Reopen the file in read-only mode ----------
    cout << "Reading University Card Details..." << endl;
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        cerr << "Error: could not open file for reading: " << strerror(errno) << endl;
        return 1;
    }

    // ---------- STEP 6: Read into a character buffer using read() ----------
    char buffer[512];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1); // leave room for '\0'
    if (bytesRead == -1) {
        cerr << "Error: read failed: " << strerror(errno) << endl;
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';   // read() does not add a terminator, so we do

    // ---------- STEP 7: Display the details on the terminal ----------
    cout << "----- UNIVERSITY CARD DETAILS -----" << endl;
    cout << buffer;
    cout << "-----------------------------------" << endl;

    // ---------- STEP 8: Close the file after reading ----------
    close(fd);
    cout << "File read successfully." << endl;

    return 0;
}