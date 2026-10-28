#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct train {
    int no;
    char name[30], src[20], dest[20];
    int total, avail;
    struct train *next;
};

struct passenger {
    int id, age;
    char name[30], gender;
    struct passenger *next;
};

struct ticket {
    int pnr, pid, tno, seat;
    struct ticket *prev, *next;
};

struct wait {
    int pid, tno;
    struct wait *next;
};

struct cancel {
    int pnr, pid, tno, seat;
    struct cancel *next;
};

struct train *trainHead = NULL;
struct passenger *passHead = NULL;
struct ticket *tickHead = NULL;
struct wait *front = NULL, *rear = NULL;
struct cancel *top = NULL;
int pnrCount = 1000;

struct train *findTrain(int no)
{
    struct train *t = trainHead;
    if (t == NULL)
        return NULL;
    do {
        if (t->no == no)
            return t;
        t = t->next;
    } while (t != trainHead);
    return NULL;
}

struct passenger *findPassenger(int id)
{
    struct passenger *p = passHead;
    while (p != NULL) {
        if (p->id == id)
            return p;
        p = p->next;
    }
    return NULL;
}

struct ticket *findTicket(int pnr)
{
    struct ticket *t = tickHead;
    while (t != NULL) {
        if (t->pnr == pnr)
            return t;
        t = t->next;
    }
    return NULL;
}

int seatTaken(int tno, int seat)
{
    struct ticket *t = tickHead;
    while (t != NULL) {
        if (t->tno == tno && t->seat == seat)
            return 1;
        t = t->next;
    }
    return 0;
}

int freeSeat(int tno, int total)
{
    int i;
    for (i = 1; i <= total; i++) {
        if (seatTaken(tno, i) == 0)
            return i;
    }
    return 0;
}

void addTrain()
{
    struct train *n, *t;
    n = (struct train *)malloc(sizeof(struct train));
    printf("Train number: ");
    scanf("%d", &n->no);
    if (findTrain(n->no) != NULL) {
        printf("Train already there\n");
        free(n);
        return;
    }
    printf("Train name: ");
    scanf("%s", n->name);
    printf("Source: ");
    scanf("%s", n->src);
    printf("Destination: ");
    scanf("%s", n->dest);
    printf("Total seats: ");
    scanf("%d", &n->total);
    n->avail = n->total;

    if (trainHead == NULL) {
        trainHead = n;
        n->next = n;
    } else {
        t = trainHead;
        while (t->next != trainHead)
            t = t->next;
        t->next = n;
        n->next = trainHead;
    }
    printf("Train added\n");
}

void printTrain(struct train *t)
{
    printf("%d\t%s\t%s\t%s\t%d\t%d\n", t->no, t->name, t->src, t->dest, t->total, t->avail);
}

void displayTrains()
{
    struct train *t = trainHead;
    if (t == NULL) {
        printf("No trains\n");
        return;
    }
    printf("No\tName\tFrom\tTo\tTotal\tFree\n");
    do {
        printTrain(t);
        t = t->next;
    } while (t != trainHead);
}

void searchTrainByNo()
{
    int no;
    struct train *t;
    printf("Train number: ");
    scanf("%d", &no);
    t = findTrain(no);
    if (t == NULL)
        printf("Train not found\n");
    else
        printTrain(t);
}

void searchTrainByRoute()
{
    char s[20], d[20];
    int found = 0;
    struct train *t = trainHead;
    printf("Source: ");
    scanf("%s", s);
    printf("Destination: ");
    scanf("%s", d);
    if (t == NULL) {
        printf("No trains\n");
        return;
    }
    do {
        if (strcmp(t->src, s) == 0 && strcmp(t->dest, d) == 0) {
            printTrain(t);
            found = 1;
        }
        t = t->next;
    } while (t != trainHead);
    if (found == 0)
        printf("No train on this route\n");
}

void trainMenu()
{
    int ch;
    do {
        printf("\n1.Add train\n2.Search by number\n3.Search by route\n4.Display trains\n5.Back\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: addTrain(); break;
        case 2: searchTrainByNo(); break;
        case 3: searchTrainByRoute(); break;
        case 4: displayTrains(); break;
        }
    } while (ch != 5);
}

void addPassenger()
{
    struct passenger *n, *p;
    n = (struct passenger *)malloc(sizeof(struct passenger));
    printf("Passenger id: ");
    scanf("%d", &n->id);
    if (findPassenger(n->id) != NULL) {
        printf("Id already used\n");
        free(n);
        return;
    }
    printf("Name: ");
    scanf("%s", n->name);
    printf("Age: ");
    scanf("%d", &n->age);
    printf("Gender (M/F): ");
    scanf(" %c", &n->gender);
    n->next = NULL;

    if (passHead == NULL)
        passHead = n;
    else {
        p = passHead;
        while (p->next != NULL)
            p = p->next;
        p->next = n;
    }
    printf("Passenger added\n");
}

void displayPassengers()
{
    struct passenger *p = passHead;
    if (p == NULL) {
        printf("No passengers\n");
        return;
    }
    printf("Id\tName\tAge\tGender\n");
    while (p != NULL) {
        printf("%d\t%s\t%d\t%c\n", p->id, p->name, p->age, p->gender);
        p = p->next;
    }
}

void searchPassenger()
{
    int id;
    struct passenger *p;
    printf("Passenger id: ");
    scanf("%d", &id);
    p = findPassenger(id);
    if (p == NULL)
        printf("Passenger not found\n");
    else
        printf("%d\t%s\t%d\t%c\n", p->id, p->name, p->age, p->gender);
}

void passengerMenu()
{
    int ch;
    do {
        printf("\n1.Add passenger\n2.Search passenger\n3.Display passengers\n4.Back\nChoice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: addPassenger(); break;
        case 2: searchPassenger(); break;
        case 3: displayPassengers(); break;
        }
    } while (ch != 4);
}

int insertTicket(int pid, int tno, int seat)
{
    struct ticket *n, *t;
    n = (struct ticket *)malloc(sizeof(struct ticket));
    pnrCount++;
    n->pnr = pnrCount;
    n->pid = pid;
    n->tno = tno;
    n->seat = seat;
    n->next = NULL;
    n->prev = NULL;

    if (tickHead == NULL)
        tickHead = n;
    else {
        t = tickHead;
        while (t->next != NULL)
            t = t->next;
        t->next = n;
        n->prev = t;
    }
    return n->pnr;
}

void enqueue(int pid, int tno)
{
    struct wait *n = (struct wait *)malloc(sizeof(struct wait));
    n->pid = pid;
    n->tno = tno;
    n->next = NULL;
    if (rear == NULL)
        front = rear = n;
    else {
        rear->next = n;
        rear = n;
    }
}

void bookTicket()
{
    int pid, tno, seat, pnr;
    struct train *t;
    printf("Passenger id: ");
    scanf("%d", &pid);
    if (findPassenger(pid) == NULL) {
        printf("Register the passenger first\n");
        return;
    }
    printf("Train number: ");
    scanf("%d", &tno);
    t = findTrain(tno);
    if (t == NULL) {
        printf("Train not found\n");
        return;
    }
    if (t->avail > 0) {
        seat = freeSeat(tno, t->total);
        pnr = insertTicket(pid, tno, seat);
        t->avail--;
        printf("Ticket booked. PNR %d, Seat %d\n", pnr, seat);
    } else {
        enqueue(pid, tno);
        printf("Seats full. Added to waiting list\n");
    }
}

void modifyReservation()
{
    int pnr, ch, seat, tno;
    struct ticket *k;
    struct train *old, *nw;
    printf("PNR: ");
    scanf("%d", &pnr);
    k = findTicket(pnr);
    if (k == NULL) {
        printf("Ticket not found\n");
        return;
    }
    old = findTrain(k->tno);
    printf("1.Change seat\n2.Change train\nChoice: ");
    scanf("%d", &ch);
    if (ch == 1) {
        printf("New seat number: ");
        scanf("%d", &seat);
        if (seat < 1 || seat > old->total)
            printf("Invalid seat\n");
        else if (seatTaken(k->tno, seat))
            printf("Seat already booked\n");
        else {
            k->seat = seat;
            printf("Seat changed\n");
        }
    } else if (ch == 2) {
        printf("New train number: ");
        scanf("%d", &tno);
        nw = findTrain(tno);
        if (nw == NULL)
            printf("Train not found\n");
        else if (nw->avail == 0)
            printf("No seats in that train\n");
        else {
            old->avail++;
            nw->avail--;
            k->tno = tno;
            k->seat = freeSeat(tno, nw->total);
            printf("Train changed. New seat %d\n", k->seat);
        }
    }
}

void push(struct ticket *k)
{
    struct cancel *n = (struct cancel *)malloc(sizeof(struct cancel));
    n->pnr = k->pnr;
    n->pid = k->pid;
    n->tno = k->tno;
    n->seat = k->seat;
    n->next = top;
    top = n;
}

void cancelTicket()
{
    int pnr, pid, seat, newpnr;
    struct ticket *k;
    struct train *t;
    struct wait *p, *q;

    printf("PNR: ");
    scanf("%d", &pnr);
    k = findTicket(pnr);
    if (k == NULL) {
        printf("Ticket not found\n");
        return;
    }
    push(k);
    t = findTrain(k->tno);
    t->avail++;

    if (k->prev == NULL)
        tickHead = k->next;
    else
        k->prev->next = k->next;
    if (k->next != NULL)
        k->next->prev = k->prev;
    free(k);
    printf("Ticket cancelled\n");

    q = NULL;
    p = front;
    while (p != NULL && p->tno != t->no) {
        q = p;
        p = p->next;
    }
    if (p != NULL) {
        if (q == NULL)
            front = p->next;
        else
            q->next = p->next;
        if (p == rear)
            rear = q;
        pid = p->pid;
        free(p);
        seat = freeSeat(t->no, t->total);
        newpnr = insertTicket(pid, t->no, seat);
        t->avail--;
        printf("Waiting passenger %d got the seat. PNR %d, Seat %d\n", pid, newpnr, seat);
    }
}

void seatAvailability()
{
    int no;
    struct train *t;
    printf("Train number: ");
    scanf("%d", &no);
    t = findTrain(no);
    if (t == NULL)
        printf("Train not found\n");
    else
        printf("Total seats %d, Available %d\n", t->total, t->avail);
}

void displayWaiting()
{
    struct wait *w = front;
    if (w == NULL) {
        printf("Waiting list is empty\n");
        return;
    }
    printf("Passenger\tTrain\n");
    while (w != NULL) {
        printf("%d\t\t%d\n", w->pid, w->tno);
        w = w->next;
    }
}

void waitingMenu()
{
    int ch, c = 0;
    struct wait *w;
    do {
        printf("\n1.Display waiting list\n2.Count\n3.Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1)
            displayWaiting();
        else if (ch == 2) {
            c = 0;
            for (w = front; w != NULL; w = w->next)
                c++;
            printf("Passengers waiting: %d\n", c);
        }
    } while (ch != 3);
}

void displayTickets()
{
    struct ticket *t = tickHead;
    if (t == NULL) {
        printf("No bookings\n");
        return;
    }
    printf("PNR\tPassenger\tTrain\tSeat\n");
    while (t != NULL) {
        printf("%d\t%d\t\t%d\t%d\n", t->pnr, t->pid, t->tno, t->seat);
        t = t->next;
    }
}

void displayCancelled()
{
    struct cancel *c = top;
    if (c == NULL) {
        printf("No cancelled tickets\n");
        return;
    }
    printf("PNR\tPassenger\tTrain\tSeat\n");
    while (c != NULL) {
        printf("%d\t%d\t\t%d\t%d\n", c->pnr, c->pid, c->tno, c->seat);
        c = c->next;
    }
}

void historyMenu()
{
    int ch;
    do {
        printf("\n1.Current bookings\n2.Cancelled tickets\n3.Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1)
            displayTickets();
        else if (ch == 2)
            displayCancelled();
    } while (ch != 3);
}

void displayAll()
{
    printf("\n--- Trains ---\n");
    displayTrains();
    printf("\n--- Passengers ---\n");
    displayPassengers();
    printf("\n--- Bookings ---\n");
    displayTickets();
    printf("\n--- Waiting list ---\n");
    displayWaiting();
    printf("\n--- Cancelled tickets ---\n");
    displayCancelled();
}

int main()
{
    int ch;
    do {
        printf("\n===== RAILWAY TICKET RESERVATION SYSTEM =====\n");
        printf("1.Train Management\n2.Passenger Management\n3.Ticket Reservation\n");
        printf("4.Modify Reservation\n5.Ticket Cancellation\n6.Seat Availability\n");
        printf("7.Waiting List Management\n8.Reservation History\n9.Display All Records\n10.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
        case 1: trainMenu(); break;
        case 2: passengerMenu(); break;
        case 3: bookTicket(); break;
        case 4: modifyReservation(); break;
        case 5: cancelTicket(); break;
        case 6: seatAvailability(); break;
        case 7: waitingMenu(); break;
        case 8: historyMenu(); break;
        case 9: displayAll(); break;
        case 10: printf("Thank you\n"); break;
        default: printf("Invalid choice\n");
        }
    } while (ch != 10);
    return 0;
}
