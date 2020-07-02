# Account Balance - BANK

import threading 
  
balance = 0

def deposit(id,value,lock): 
    global balance
    lock.acquire()
    balance = balance+value
    print("Thread ",id," deposit: ",value)
    print("Balance: ",balance)
    lock.release()

    
def withdraw(id,value,lock): 
    global balance
    lock.acquire()
    balance = balance-value
    print("Thread ",id," withdraw: ",value)
    print("Balance: ",balance)
    lock.release()
  
lock = threading.Lock()
t1 = threading.Thread(target=deposit, args=(1,1000,lock)) 
t2 = threading.Thread(target=withdraw, args=(2,100,lock)) 
t3 = threading.Thread(target=deposit, args=(1,2000,lock)) 
t4 = threading.Thread(target=deposit, args=(1,3000,lock)) 
t5 = threading.Thread(target=withdraw, args=(2,1500,lock)) 

t1.start()  
t2.start()
t3.start() 
t4.start() 
t5.start() 

t1.join() 
t2.join() 
t3.join() 
t4.join() 
t5.join() 


print("FINAL BALANCE:", balance)
