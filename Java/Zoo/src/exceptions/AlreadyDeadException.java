package exceptions;

public class AlreadyDeadException extends Throwable {
    public AlreadyDeadException() {
        System.out.println("The pet is already dead !");
    }
}
