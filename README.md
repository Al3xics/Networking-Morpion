# Morpion

## This game was made in 1 week, with 3 people.

Right clic on your project name, then go to **properties** :
<br/>

- In **Configurations Properties**, go to **Debugging** --> **Environment**.<br/>
Then add this : **PATH=$(ProjectDir)SFML-2.6.1\bin**

- Select the **Debug Client** configuration. Go to **Debugging** --> **Command Arguments**.<br>
Then add this : **client**

- Select the **Debug Server** configuration. Go to **Debugging** --> **Command Arguments**.<br>
Then add this : **server**
<br/>
<br>

If you want to launch both the server and client at the same time, open twice the **.sln** file.<br>
Set yourself to the **Debug Client** configuration on one, and **Debug Server** on the other.<br>
Now start the server first, then the client. <br>
You will have to enter your name on the terminal. Please first enter the player's name on the server terminal, then that of the client.<br>
You now have the client and server for this game.<br>
<br>

Please note that due to lack of time, the grid does not send and receive data. On the other hand, the chat has it. So you can communicate between the two games.<br>

Still due to lack of time, we cannot play this game remotely either.
<br/>
<br/>
<br/>

[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/S8Vx12Bd)
