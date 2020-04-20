
// Account Balance : withdrawal - 10 times
// 				     deposit - 5 times

class accbalance{
	public static int balance = 0;

	public static class deposit implements Runnable {
		int amt;
		public deposit(int amt) {
			this.amt = amt;
		}

		public void run() {
			synchronized (accbalance.class) {
				balance += this.amt;
				System.out.println("Amount Adding into the account "+this.amt);
				System.out.println("Total Balance "+balance);
				System.out.println(Thread.currentThread().getName()+" Deposited Successfully\n");
			}
		}
	} 

	public static class withdraw implements Runnable {
		int amt;
		public withdraw(int amt) {
			this.amt = amt;
		}

		public void run() {
			synchronized (accbalance.class) {
				if(balance<100){
					System.out.println("Can not withdraw due to insufficient balance in account\n");
				}
				else{
					balance -= this.amt;
					System.out.println("Amount Removing from account "+this.amt);
					System.out.println("Total Balance "+balance);
					System.out.println(Thread.currentThread().getName()+" Withdraw Successful\n");
				}
			}
		}
	}

	public static void main(String[] args) throws InterruptedException {

		Thread[] withdraw = new Thread[10];
		Thread[] deposit = new Thread[5];

		withdraw[0] = new Thread(new withdraw(100), "thread_w0");
		withdraw[1] = new Thread(new withdraw(120), "thread_w1");
		withdraw[2] = new Thread(new withdraw(140), "thread_w2");
		withdraw[3] = new Thread(new withdraw(160), "thread_w3");
		withdraw[4] = new Thread(new withdraw(180), "thread_w4");
		withdraw[5] = new Thread(new withdraw(200), "thread_w5");
		withdraw[6] = new Thread(new withdraw(220), "thread_w6");
		withdraw[7] = new Thread(new withdraw(240), "thread_w7");
		withdraw[8] = new Thread(new withdraw(260), "thread_w8");
		withdraw[9] = new Thread(new withdraw(280), "thread_w9");


		deposit[0] = new Thread(new deposit(1000), "thread_d0");
		deposit[1] = new Thread(new deposit(1500), "thread_d1");
		deposit[2] = new Thread(new deposit(1100), "thread_d2");
		deposit[3] = new Thread(new deposit(1800), "thread_d3");
		deposit[4] = new Thread(new deposit(1200), "thread_d4");

		for(int i = 0; i < 10; i++)
        {
            withdraw[i].join();
        }
        for(int i = 0; i < 5; i++)
        {
            deposit[i].join();
        }

		deposit[0].start();
		withdraw[0].start();
		deposit[1].start();
		deposit[2].start();
		deposit[3].start();
		withdraw[1].start();
		withdraw[2].start();
		withdraw[3].start();
		withdraw[4].start();
		deposit[4].start();
		withdraw[5].start();
		withdraw[6].start();
		withdraw[7].start();
		withdraw[8].start();
		withdraw[9].start();
	}

}