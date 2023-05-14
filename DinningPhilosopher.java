import java.util.Scanner;

class Philosopher implements Runnable {
    // The forks on either side of this Philosopher
    private Object leftFork;
    private Object rightFork;

    public Philosopher(Object leftFork, Object rightFork) {
        this.leftFork = leftFork;
        this.rightFork = rightFork;
    }

    private void doAction(String action) throws InterruptedException {
        System.out.println(
                Thread.currentThread().getName() + " " + action);
        Thread.sleep(((int) (Math.random() * 100)));
    }

    @Override
    public void run() {
        try {
            // thinking
            doAction(": Thinking");
            synchronized (leftFork) {
                doAction(": Picked up left fork");
                synchronized (rightFork) {
                    // eating
                    doAction(": Picked up right fork - eating");

                    doAction(": Put down right fork");
                }

                // Back to thinking
                doAction(": Put down left fork. Back to thinking");
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            return;
        }
    }
}

public class DinningPhilosopher {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);

        int number = sc.nextInt();

        Philosopher[] philosophers = new Philosopher[number];
        Object[] forks = new Object[philosophers.length];

        for (int i = 0; i < forks.length; i++) {
            forks[i] = new Object();
        }

        for (int i = 0; i < philosophers.length; i++) {
            Object leftFork = forks[i];
            Object rightFork = forks[(i + 1) % forks.length];

            if (i == philosophers.length - 1) {
                // The last philosopher picks up the right fork first
                philosophers[i] = new Philosopher(rightFork, leftFork);
            } else {
                philosophers[i] = new Philosopher(leftFork, rightFork);
            }

            Thread t = new Thread(philosophers[i], "Philosopher " + (i + 1));
            t.start();
        }

        sc.close();
    }
}
