# Railway Ticket Reservation System

Mini project for IT23302 Data Structures, written in C.

## Data structures used
- Circular linked list: train management
- Singly linked list: passenger management
- Doubly linked list: ticket reservation
- Queue: waiting list
- Stack: cancellation history

## How to run
```
gcc rail.c -o rail
./rail
```

## Sample Output
Train 101 has only 2 seats, so the third booking goes to the waiting list. When PNR 1001 is cancelled, the waiting passenger gets the seat.

```
Enter your choice: 3
Passenger id: 10
Train number: 101
Ticket booked. PNR 1001, Seat 1

Enter your choice: 3
Passenger id: 11
Train number: 101
Ticket booked. PNR 1002, Seat 2

Enter your choice: 3
Passenger id: 12
Train number: 101
Seats full. Added to waiting list

Enter your choice: 6
Train number: 101
Total seats 2, Available 0

Enter your choice: 5
PNR: 1001
Ticket cancelled
Waiting passenger 12 got the seat. PNR 1003, Seat 1

Enter your choice: 8
1.Current bookings
2.Cancelled tickets
3.Back
Choice: 2
PNR     Passenger       Train   Seat
1001    10              101     1
```

## Team
- Kathir (2025115079)
- Kamesh P (2025115013)
- Dilliganesh R (2025115095)
