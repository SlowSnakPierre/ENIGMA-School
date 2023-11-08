package exceptions;

public class FullZooException extends Throwable {
    public FullZooException() {
        System.out.println("Zoo is already full !");
    }
}
