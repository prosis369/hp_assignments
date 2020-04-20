class extendthread extends Thread {
	extendthread(String name) {
		super(name);
	}
	@Override
	public void run() {
		System.out.println("Executing thread: "+Thread.currentThread().getName());
		System.out.println(Thread.currentThread().getName()+" ID: "+Thread.currentThread().getId());
	}
	public static void main(String[] args){
		extendthread t1 = new extendthread("Thread 1");
		t1.start();
		extendthread t2 = new extendthread("Thread 2");
		t2.start();
		extendthread t3 = new extendthread("Thread 3");
		t3.start();
	}
}