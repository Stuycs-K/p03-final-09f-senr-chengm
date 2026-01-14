# Dev Log:

This document must be updated daily every time you finish a work session.

## Matthew Cheng

### 2026-01-06 - Starting changes
-Renamed DEVLOGS, added correct names
-Added files
-Fixed header code for networkstructure.c and server.c
-Added all helper functions and their headers ( view, create, remove )
-Added helper function command logic to server and client loops
-Added shared memory through create command, also renamed file name that stores the messages

### 2026-01-07 - Discussion and Code
-Discussed with partner about what to do
-Added write command in server to write to the file ( store the story )
-Inserted, but commented, possible semaphore code while writing

### 2026-01-08 - Fixing up server, removing unnecssary code, overall revamp of code
-Removed view file code in client because client doesn't access file
-Fixed server write code by adding file descriptor, include statement
-Removed create and rem commands in server for now, also server bugfixing
-Compiled and tested username and message sending back and forth

-Commented out subserver code to switch out of forking server
-Added server code and logic with select
-Added / replaced client code and logic with select

### 2026-01-09 - Trying to fix updated server and client code
-Added client print message to prompt user for messages / input
-Working and discussing with partner about a plan for the MVP

### 2026-01-11 - More overall changes and bugfixes
-Tried adjust server code to not use forking
-Adjusted select code and added client tracking code in server
-Finished adding new server code
-Add client connection code in server

### 2026-01-12 - Adding onto MVP, added notification when new client joins
-Added server code that notifies online clients when a new client joins the group chat.
-Added server code that notifies online clients when a client leaves / disconnects from the group chat.
-Notifies online clients how many online clients there are / remain.

### 2026-01-13 - More add on to MVP, allowing different computer communication, store usernames
-Edited networking getaddrinfo to be able to chat with clients from other computers
-Added client username question when new client connects to server.
