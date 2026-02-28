"""
import random


print("welcome to rps!!!")
user_score = 0
computer_score = 0
exit_flag = False
userwon_flag = False
computerwon_flag = False

while not exit_flag:
    user_choice = input("Enter rock, paper, or scissors (press q to end game): ")
    if user_choice not in ["rock", "paper", "scissors", "q"]:
        print("invalid input! please enter rock, paper, or scissors")
        continue
    if user_choice == ("q"):
        exit_flag = True   
        break 
    computer_choice = random.choice(["rock", "paper", "scissors"])
    print("computer chose:", computer_choice)
    if user_choice == computer_choice:
        print("It's a draw!")
    elif (user_choice=="rock" and computer_choice == "scissors"):
        userwon_flag = True
    elif (user_choice=="scissors" and computer_choice == "paper"):
        userwon_flag =True
    else:
        print("computer wins this round")
        computer_score += 1
        print("current score of user", user_score, "| computer:", computer_score)

    # Conditions for each win scenario
    if userwon_flag:
        print("you win this round")
        user_score+= 1  
        print("current score of user", user_score, "| computer:", computer_score)
        userwon_flag = False
    elif computerwon_flag:
          print("computer wins this round")
          computer_score += 1
          print("current score of user", user_score, "| computer:", computer_score)
          computerwon_flag = True
    
    
print("\nGame Ended")
print("final score:")
print("you", user_score)
print("computer:",computer_score)
if user_score > computer_score:
    print("congratulations you won the game")
elif computer_score > user_score:
    print("computer won the game")
else: 
    print("the game is draw")            
"""
# digital wallet 




FILE_NAME = "wallet.txt"


def register():
    phone = input("Enter phone number: ")
    pin = input("Enter your 4-digit Pin: ")

    file = open("wallet.txt", "a")
    file.write(phone + " " + pin + " 0\n")   
    file.close()

    print("Account created successfully!")


def login():
    phone = input("Enter phone number: ")
    pin = input("Enter PIN: ")

    file = open("wallet.txt", "r")
    lines = file.readlines()
    file.close()

    for line in lines:
        data = line.strip().split(" ")

        if data[0] == phone and data[1] == pin:
            print("Login successful!")
            wallet_menu(phone)
            return   

    print("Wrong phone or PIN!")



def check_balance(phone):
    file = open("wallet.txt", "r")
    lines = file.readlines()
    file.close()

    for line in lines:
        data = line.strip().split(" ")

        if data[0] == phone:
            print("Your Balance:", data[2])
            return

def deposit(phone):
    amount_input = input("Enter amount to deposit: ")

  
    amount_input = amount_input.replace(",", "")

    try:
        amount = int(amount_input)
    except ValueError:
        print("Invalid amount! Enter numbers only.")
        return

    file = open("wallet.txt", "r")
    lines = file.readlines()
    file.close()

    file = open("wallet.txt", "w")

    for line in lines:
        data = line.strip().split(" ")

        if data[0] == phone:
            new_balance = int(data[2]) + amount
            file.write(data[0] + " " + data[1] + " " + str(new_balance) + "\n")
        else:
            file.write(line)

    file.close()
    print("Deposit successful!")


def send_money(sender):
    receiver = input("Enter receiver phone: ")
    amount_input = input("Enter amount: ")

    amount_input = amount_input.replace(",", "")

    try:
        amount = int(amount_input)
    except ValueError:
        print("Invalid amount!")
        return

    file = open("wallet.txt", "r")
    lines = file.readlines()
    file.close()

    file = open("wallet.txt", "w")

    for line in lines:
        data = line.strip().split(" ")

        if data[0] == sender:
            if int(data[2]) >= amount:
                new_balance = int(data[2]) - amount
                file.write(data[0] + " " + data[1] + " " + str(new_balance) + "\n")
            else:
                print("Not enough balance!")
                file.write(line)

        elif data[0] == receiver:
            new_balance = int(data[2]) + amount
            file.write(data[0] + " " + data[1] + " " + str(new_balance) + "\n")

        else:
            file.write(line)

    file.close()
    print("Transaction completed!")



def wallet_menu(phone):
    while True:
        print("\n1. Check Balance")
        print("2. Deposit")
        print("3. Send Money")
        print("4. Logout")

        choice = input("Choose option: ")

        if choice == "1":
            check_balance(phone)
        elif choice == "2":
            deposit(phone)
        elif choice == "3":
            send_money(phone)
        elif choice == "4":
            print("Logged out!")
            break
        else:
            print("Invalid choice!")


while True:
    print("\n=== Terminal Wallet ===")
    print("1. Register")
    print("2. Login")
    print("3. Exit")

    choice = input("Choose option: ")

    if choice == "1":
        register()
    elif choice == "2":
        login()
    elif choice == "3":
        print("Goodbye!")
        break
    else:
        print("Invalid choice!")
   



    

    
   

