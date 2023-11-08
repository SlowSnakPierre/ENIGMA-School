package bo;

import exceptions.*;

import java.util.ArrayList;
import java.util.List;

public class Zoo {

    private Manager manager;
    private int nbMax;
    private final List<Animal> alAnimal = new ArrayList<>();

    public Zoo(Manager manager, int nbMax) {
        this.manager = manager;
        this.nbMax = nbMax;
    }

    public boolean add(Animal animal) throws AlreadyDeadException, FullZooException {
        if (this.nbMax > this.alAnimal.size()) {
            if (animal.getAgeMax() > animal.getAge()) {
                this.alAnimal.add(animal);
                return true;
            } else {
                throw new AlreadyDeadException();
            }
        } else {
            throw new FullZooException();
        }
    }

    public boolean remove() throws EmptyZooException {
        if (this.alAnimal.isEmpty()) {
            throw new EmptyZooException();
        }

        System.out.println(this.alAnimal.remove(this.alAnimal.size() - 1));
        return true;
    }

    public void birthZoo() throws EmptyZooException {
        if (this.alAnimal.isEmpty()) {
            throw new EmptyZooException();
        }

        for (int i = 0; i < this.alAnimal.size(); i++) {
            Animal animal = (Animal)(this.alAnimal.get(i));
            boolean isDead = animal.getOlder();
            if (!isDead) {
                //noinspection SuspiciousListRemoveInLoop
                this.alAnimal.remove(i);
            }
        }
    }

    public void feedAnimal() throws EmptyZooException {
        if (this.alAnimal.isEmpty()) {
            throw new EmptyZooException();
        }
        for (Animal animal : this.alAnimal) {
            System.out.println(animal.eat());
        }
    }

    public void listZoo() {
        System.out.println(this.manager);
        for (Animal animal : this.alAnimal) {
            System.out.println(animal);
        }
    }
}
