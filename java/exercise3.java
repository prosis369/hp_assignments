class runnablethread implements Runnable {
	public void run() {
		System.out.println("Executing thread "+Thread.currentThread().getName());
		System.out.println(Thread.currentThread().getName()+" ID: "+Thread.currentThread().getId());
	}
	public static void main(String[] args) {
		Thread t1 = new Thread(new runnablethread(), "Thread 1");
		t1.start();
		Thread t2 = new Thread(new runnablethread(), "Thread 2");
		t2.start();
		Thread t3 = new Thread(new runnablethread(), "Thread 3");
		t3.start();
	}
}