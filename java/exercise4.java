class sleepinterrupt implements Runnable {
	public void run() {
	while(!Thread.interrupted()) {}
	System.out.println(Thread.currentThread().getName()+": Interrupt");
}
	public static void main(String[] args) throws InterruptedException {
		Thread t1 = new Thread(new sleepinterrupt(), "Thread 1");
		t1.start();
		System.out.println(Thread.currentThread().getName()+": Sleeps for 3s");
		Thread.sleep(3000);
		System.out.println(Thread.currentThread().getName()+": Interrupt");
		t1.interrupt();
	}
}