package go;

import bo.*;
import exceptions.AlreadyDeadException;
import exceptions.EmptyZooException;
import exceptions.FullZooException;

public class Main {
    private static int rand(int min, int max) {
        return (int) (Math.random() * (max - min)) + min;
    }

    public static void main(String[] args) throws EmptyZooException, AlreadyDeadException, FullZooException {
        Manager manager = new Manager("Petter", rand(5, 30));
        Zoo zoo = new Zoo(manager, 5);

        Animal bird = new Bird("Ziyad", rand(0,5), "Grey");
        Animal catlike = new CatLike("Aurélien", rand(0,5), "Cat");

        Animal monkey = new Monkey("Cyborg", rand(0,5));

        zoo.add(bird);
        zoo.add(catlike);
        zoo.add(monkey);
        zoo.listZoo();
        System.out.println();

        zoo.feedAnimal();
        zoo.birthZoo();
        System.out.println();

        zoo.listZoo();
    }
}