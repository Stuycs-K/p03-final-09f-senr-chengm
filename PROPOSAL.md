# Final Project Proposal

## Group Members:

Rohan Sen, Matthew Cheng

# Intentions:

We want to make a messaging app that allows users to choose and message other active users. The main technical hurdle is matching the clients together.

# Intended usage:

- On start asks for username
- List of other existing users
- Open messages with user and receive info of client from server
- message user, then wait for response

# Technical Details:

- Creating chat server to message people (mem alloc) - Both
- webserver used to store data in a file (sockets, files, forking) - Both
- Select used to read from the clients - Matthew
- a list of chats with other users to pick from - Both
- username asked for when client starts, used to load chats with others if present on server - Rohan
- IF TIME PERMITS: GTK front end - Rohan

# Intended pacing:

1/6 end of day or 1/7 start of class:  
- Basic skeleton / pseudocode plan set up  
- Determine all files to be used  
- Determine all helper functions needed, add skeletons for those  
- Makefile complete
- Start coding, get memory allocation started

1/7 end of day or 1/8 start of class
- Start and finish memory allocation
- Complete helper functions ( like view, etc. )
- Start socket logic

1/8 end of day or 1/9 start of class
- Continue, possibly finish socket logic
- Start and maybe finish server and client code / logic
- MAYBE TESTING
Weekend:
- Finish up code for MVP
- TESTING TESTING TESTING
1/12 - 1/13
- Have a MVP: including ability to chat / connect between two clients
- Maybe being able to choose which client to talk to?
1/13 - 1/16
- Finish adding extra features
- Viewing all possible clients / online users for chatting
- Client username input to load chats with specific clients
- Maybe a group chat feature
- Maybe front end code to make design look better
