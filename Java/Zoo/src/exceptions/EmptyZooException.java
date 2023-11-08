package exceptions;

public class EmptyZooException extends Throwable {
    public EmptyZooException() {
        System.out.println("Zoo is empty !");
    }
}
