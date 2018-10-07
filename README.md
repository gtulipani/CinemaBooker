# CinemaBooker
## Description
CLI Multi-Threading Server-Client Application that represents a 
system to book tickets for a film. The server parses different [csv](https://en.wikipedia.org/wiki/Comma-separated_values) 
files with the available rooms, movies and the showings per day. The client 
can ask for
  information or book seats for a given showing through a [Socket](https://en.wikipedia.org/wiki/Network_socket).

## Multi-Threading
##### Threads Generation
The Server handles several threads simultaneously:
- `main`: parses the input files, throws a new thread called **AccepterThread**
 and continues with the execution until a `q` letter is detected in stdin.
-  `AccepterThread`: this thread is waiting for new connections through the 
socket and throwing a new thread called **ClientThread** for each one of them.
- `ClientThread`: this thread is the one that receives and process each one 
of the commands received through the socket
##### Data Race Conditions
The Race Conditions have been resolved using a [Monitor](https://en.wikipedia.org/wiki/Monitor_(synchronization))
class for the shared resources (Rooms, Movies and Showings).

## Communication Protocol
##### Message Handling
Both Client and Server communicate through a Socket using the [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)
Protocol. The logic to handle the Sockets is written in [C](https://en.wikipedia.org/wiki/C_(programming_language)) 
and it's being managed using a [wrapper](https://en.wikipedia.org/wiki/Wrapper_function). 
The protocol has been defined the following way, to facilitate the reception of 
messages:
1. The server opens a socket on the port received as parameter and waits for 
new connections
1. The client connects to the host and port received as parameters and start 
sending messages with commands:
   1. The client sends a 4 Bytes [Big Endian](https://en.wikipedia.org/wiki/Endianness#Big-endian) 
   (which is the same as [Network Endian](https://en.wikipedia.org/wiki/Endianness#Networking))
   int with the quantity of bytes from the command to be sent.
   1. The server receives the int and knows how many bytes to wait for in the
    socket.
   1. The client sends the actual command to the server
   1. The server process the command and prepares the answer, by sending 
   first a integer with the quantity of bytes and finally the complete message.
   1. The client receives both the integer with the quantity of bytes and 
   prints the response in stdout
##### Connection End
When the Client finishes executing all its commands, it [shutdowns](http://man7.org/linux/man-pages/man2/shutdown.2.html)
the socket for both Reading and Writing and closes it entirely.
On the server side, the ClientThread was waiting for a new message using the 
[`recv()`](http://man7.org/linux/man-pages/man2/recvmsg.2.html) function. 
When the socket is closed, it returns **zero**, and the ClientThread is 
marked as dead, so that the AccepterThread detects it and kill it.

## Commands
The server application accepts the following commands to be executed:
##### List Movies by Language
###### Syntax
The command must respect the following syntax: `IDIOMA <Language>`. E.g:
```
IDIOMA ESP
```
###### Response
All the movies with that language are sent through the socket. E.g:
```
Megalodon (Castellano)
Hotel Transylvania 14
```
##### List Movies by Age Restriction
###### Syntax
The command must respect the following syntax: `EDAD <Age Restriction>`. E.g:
```
EDAD ATP
```
###### Response
All the movies with that age restriction are sent through the socket. E.g:
```
Hotel Transylvania 14
```
###### Error
If the age restriction is invalid, the following error message is sent 
through the socket:
```
Edad no reconocida
```
##### List Movies by Genre
###### Syntax
The command must respect the following syntax: `GENERO <Genre>`. E.g:
```
GENERO Terror
```
###### Response
All the movies with that genre are sent through the socket. E.g:
```
12 Horas para Sobrevivir
```
###### Error
If the genre is invalid, the following error message is sent 
through the socket:
```
Genero no reconocido
```
##### List Showings for Day
###### Syntax
The command must respect the following syntax: `FECHA <DD/MM/YYYY>`. E.g:
```
FECHA 13/10/2018
```
###### Response
All the showings that take place in that day are 
sent through the socket following the format:
```
(Id Funcion): <Funcion para "(Title)" en la sala (Room ID) con fecha (DD/MM/YYYY) - (hh:mm)> [AGOTADA]
```
The last keyword (`AGOTADA`) is 
 included only for these showings without any available seats. E.g:
```
1: <Funcion para "Megalodon (Castellano)" en la sala A con fecha 13/10/2018 - 12:00> AGOTADA
2: <Funcion para "Megalodon (Subtitulada)" en la sala B con fecha 13/10/2018 - 12:00>
3: <Funcion para "12 Horas para Sobrevivir" en la sala A con fecha 13/10/2018 - 17:00>
4: <Funcion para "Hotel Transylvania 14" en la sala B con fecha 13/10/2018 - 17:00>
```
##### List Seats for a Showing
###### Syntax
The command must respect the following syntax: `ASIENTOS <Showings ID>`. E.g:
```
ASIENTOS 2
```
###### Response
All the seats from that showing are being sent through the socket, 
representing with a `O` when the seat is available and with a `X` when it's 
already occupied. E.g:
```
2: <Funcion para "Megalodon (Subtitulada)" en la sala B con fecha 13/10/2018 - 12:00>
       1      2      3      4      5      6
A      O      O      O      O      O      O
B      O      O      O      X      X      O
C      O      X      X      X      O      O
D      X      X      O      O      O      O
E      O      O      O      O      O      O
```
##### Book Seat
###### Syntax
The command must respect the following syntax: `RESERVA <Showing ID> <Row 
Letter> <Column Number>`. E.g: `RESERVA 2 A 1`
###### Response
A success message is sent through the socket:
```
OK
```
###### Error
If the seat is already booked, the following error message is sent through 
the socket:
```
ERROR: El asiento ya esta reservado
```


## Building and Running
### Build
1. Navigate to the `src` folder
1. Execute `make -f Makefile_client_server`
1. The Makefile takes all the following files:
   1. The files whose name start with `server` are the ones used by the server.
   1. The files whose name start with `client` are the ones used by the client.
   1. The files whose name start with `commons` are the ones used by both 
  client and server

### Run
#### Server
The server must be executed with the following syntax:
```
./server [port] [rooms_file] [movies_file] [showings_file]
```
##### Configuration Files
###### Rooms CSV
The Rooms File has the format `<Room ID>,<Type>,<Capacity>`. E.g:
```
A,2D,grande
B,3D,mediana
C,4D,chica
```
The application accepts the following values:
1. `Type`: accepts **2D**, **3D** or **4D**.
1. `Capacity`: accepts:
   1. `chica`: contains 5 rows and 6 columns
   1. `mediana`: contains 10 rows and 11 columns
   1. `grande`: contains 15 rows and 16 columns
###### Movies CSV
The Movies File has the format `<Title>,<Language>,<Age Restriction>,
<Genre>`:
```
Megalodon (Castellano),ESP,+13,Comedia
```
The application accepts the following values:
1. `Language`: accepts **ESP** (_Spanish_) or **SUB** (_Subtitled in Spansish_).
1. `Age Restriction`: accepts **ATP**, **+13** or **+18**.
1. `Genre`: accepts:
   1. `Drama`
   1. `Accion`
   1. `Comedia`
   1. `Animacion`
   1. `Terror`
   1. `Suspenso`
###### Showings CSV
The Showings File has the format `<Room ID>,<Title>,<Date>,<Start Time>`:
```
A,Megalodon (Castellano),25/09/2018,18:00
B,Megalodon (Castellano),25/09/2018,18:00
C,Megalodon (Castellano),25/09/2018,18:00
```
The application accepts the following values:
1. `Date`: must have the **DD/MM/YYYY** format.
1. `Start Time`: must have the **hh:mm** format.
##### Standard In
The server __main__ thread will continue listening in standard in waiting for a 
`q` letter. When it's detected, it means that the server will make a _soft_ 
kill from the successive threads:
1. The server will close the socket, interrupting the [`accept()`](http://man7.org/linux/man-pages/man2/accept.2.html) method from 
the AccepterThread, forcing to not accept any more connections and asking to 
[rejoin](http://www.cplusplus.com/reference/thread/thread/join/).
1. The AccepterThread will then _kill_ the threads, by setting a health flag 
to false.
1. Each ClientThread will finish the conversation and **after that** they 
will join to the AccepterThread

This means that the main application **won't** force the Threads to stop, it 
will
 just stop accepting any more new connections and wait for the ongoing ones 
 to finish.
##### Standard Error
The server will only print messages in **stderr** in the following scenarios:
- File passed as parameter is not found/couldn't be opened:
```
El archivo <file_path> no existe.
```
- Wrong quantity of arguments:
```
Uso: ./server <puerto> <salas.csv> <peliculas.csv> <funciones.csv>
```
- Non-existing Room referenced in Showings file: 
```
La sala <Room ID> no existe en el sistema.
```
- Non-existing Movie referenced in Showings file: 
```
La película <Title> no existe en el sistema.
```
#### Client
The client must be executed with the following syntax:
```
./client [host] [port]
```
##### Standard In
The client will continue processing all the commands detected from stdin, 
until either the [EOF](https://es.wikipedia.org/wiki/EOF) is detected or an empty
line is entered (traditionally by clicking ENTER).
##### Standard Out
All the messages returned by the server through the socket will be printed in
 stdout.
##### Standard Error
The client will only print messages in **stderr** in the following scenario:
1. Wrong quantity of arguments:
```
Uso: ./client <ip-servidor> <puerto-servidor>
```

### Examples
##### List Seats
  - Start the server with the following command:
```
./server 8080 01_rooms.csv 01_movies.csv 01_showings.csv
```
  - Start one client with the following command: 
```
./client localhost 8080 < 01_client1.in
```
  - The client displays following output and finishes:
```
1: <Funcion para "Megalodon (Castellano)" en la sala A con fecha 25/09/2018 - 18:00>
Asientos:
1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16
A	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
B	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
C	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
D	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
E	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
F	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
G	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
H	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
I	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
J	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
K	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
L	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
M	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
N	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O	O
2: <Funcion para "Megalodon (Castellano)" en la sala B con fecha 25/09/2018 - 18:00>
Asientos:
1	2	3	4	5	6	7	8	9	10	11
A	O	O	O	O	O	O	O	O	O	O	O
B	O	O	O	O	O	O	O	O	O	O	O
C	O	O	O	O	O	O	O	O	O	O	O
D	O	O	O	O	O	O	O	O	O	O	O
E	O	O	O	O	O	O	O	O	O	O	O
F	O	O	O	O	O	O	O	O	O	O	O
G	O	O	O	O	O	O	O	O	O	O	O
H	O	O	O	O	O	O	O	O	O	O	O
I	O	O	O	O	O	O	O	O	O	O	O
J	O	O	O	O	O	O	O	O	O	O	O
3: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00>
Asientos:
1	2	3	4	5	6
A	O	O	O	O	O	O
B	O	O	O	O	O	O
C	O	O	O	O	O	O
D	O	O	O	O	O	O
E	O	O	O	O	O	O
```
##### Book Seats and Fill Room (2 Clients)
  - Start the server with the following command:
```
./server 8080 02_rooms.csv 02_movies.csv 02_showings.csv
```
  - Start one client with the following command:
```
./client localhost 8080 < 02_client1.in
```
  - The client displays following output and finishes:
```
3: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00>
Asientos:
1	2	3	4	5	6
A	O	O	O	O	O	O
B	O	O	O	O	O	O
C	O	O	O	O	O	O
D	O	O	O	O	O	O
E	O	O	O	O	O	O
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
3: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00>
Asientos:
1	2	3	4	5	6
A	X	X	X	X	X	X
B	X	X	X	X	X	X
C	X	X	X	X	X	X
D	X	O	O	O	O	O
E	O	O	O	O	O	O
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
OK
3: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00> AGOTADA
Asientos:
1	2	3	4	5	6
A	X	X	X	X	X	X
B	X	X	X	X	X	X
C	X	X	X	X	X	X
D	X	X	X	X	X	X
E	X	X	X	X	X	X
```
  - Start a second client with the following command:
```
./client localhost 8080 < 02_client2.in
```
  - The client displays following output and finishes:
```
1: <Funcion para "Megalodon (Castellano)" en la sala A con fecha 25/09/2018 - 18:00>
2: <Funcion para "Megalodon (Castellano)" en la sala B con fecha 25/09/2018 - 18:00>
3: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00> AGOTADA
```
##### List Movies by Language, Genre or Age (3 Clients)
  - Start the server with the following command:
```
./server 8080 03_rooms.csv 03_movies.csv 03_showings.csv
```
  - Start one client with the following command:
```
./client localhost 8080 < 03_client1.in
```
  - The client displays following output and finishes:
```
Historias de Ultratumba (Castellano)
Historias de Ultratumba (Subtitulada)
```
  - Start a second client with the following command:
```
./client localhost 8080 < 03_client2.in
```
  - The client displays following output and finishes:
```
1945
Historias de Ultratumba (Castellano)
Historias de Ultratumba (Subtitulada)
Megalodon (Castellano)
```
  - Start a third client with the following command:
```
./client localhost 8080 < 03_client3.in
```
  - The client displays following output and finishes:
```
1: <Funcion para "Megalodon (Castellano)" en la sala A con fecha 25/09/2018 - 18:00>
2: <Funcion para "Megalodon (Castellano)" en la sala C con fecha 25/09/2018 - 18:00>
3: <Funcion para "1945" en la sala B con fecha 25/09/2018 - 18:00>
9: <Funcion para "Hotel Transylvania 14" en la sala C con fecha 25/09/2018 - 14:00>
```

### Analyze Code Style
1. Navigate to the `src` folder
1. Execute the following command that uses the cpplint script provided by 
Google and the filters, both already included in the repo
```
python ./cpplint.py --extensions=h,hpp,c,cpp --filter=`cat 
filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'`
```
1. The script will start analyzing each file. Example output:
```
Done processing ./server_InputFileException.h
Done processing ./server_InvalidInputParamsException.h
Done processing ./server_LargeRoom.cpp
Done processing ./commons_Socket.h
Done processing ./server_ShowingsInputFileException.h
Done processing ./server_Showing.h
Done processing ./server_Room.cpp
Done processing ./server_CinemaMonitor.cpp
Done processing ./client.cpp
Done processing ./server_RoomCreator.cpp
Done processing ./server_SmallRoom.h
Done processing ./server_ClientOperationException.cpp
Done processing ./server_InvalidInputParamsException.cpp
Done processing ./server_ClientThread.h
Done processing ./server_CSVIterator.h
Done processing ./server_CSVRow.cpp
Done processing ./server.cpp
Done processing ./commons_Socket.cpp
Done processing ./commons_socket_t.h
Done processing ./server_AccepterThread.cpp
Done processing ./server_Thread.cpp
Done processing ./server.h
Done processing ./server_Movie.h
Done processing ./commons_ClientClosedSocketException.cpp
Done processing ./server_CSVIterator.cpp
Done processing ./server_InputFileException.cpp
Done processing ./commons_socket_t.cpp
Done processing ./server_Showing.cpp
Done processing ./server_SmallRoom.cpp
Done processing ./server_LargeRoom.h
Done processing ./server_CinemaMonitor.h
Done processing ./server_ClientThread.cpp
Done processing ./server_ShowingsInputFileException.cpp
Done processing ./server_RoomCreator.h
Done processing ./server_Thread.h
Done processing ./server_MediumRoom.cpp
Done processing ./commons_ClientClosedSocketException.h
Done processing ./server_Room.h
Done processing ./client.h
Done processing ./server_AccepterThread.h
Done processing ./server_ClientOperationException.h
Done processing ./server_CSVRow.h
Done processing ./commons_ConnectionRefusedException.h
Done processing ./server_Movie.cpp
Done processing ./server_MediumRoom.h
Done processing ./client_main.cpp
Done processing ./commons_ConnectionRefusedException.cpp
Done processing ./server_main.cpp
Total errors found: 0

```

### Clean
1. Navigate to the `src` folder
1. Execute `make -f Makefile clean`. This will remove both executables 
(_client and server_) and all the **.o** files.
