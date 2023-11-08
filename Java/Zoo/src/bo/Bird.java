package bo;

public class Bird extends Animal {
    private String color;

    public Bird(String name, int age, String color) {
        super(name, age, 8, "Cui-Cui !");
        this.color = color;
    }

    public String getColor() {
        return color;
    }

    @Override
    public String toString() {
        return this.getName() + " is a "+getClass().getName().substring(3)+", he is " + this.getAge() + " years old";
    }
}