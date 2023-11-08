package bo;

public class Monkey extends Animal {

    public Monkey(String name, int age) {
        super(name, age, 16, "Hoo Hoo Hah Hoo Ha !");
    }

    @Override
    public String toString() {
        return this.getName() + " is a "+getClass().getName().substring(3)+", he is " + this.getAge() + " years old";
    }
}