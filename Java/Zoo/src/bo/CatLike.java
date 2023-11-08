package bo;

public class CatLike extends Animal {
    private String race;

    public CatLike(String name, int age, String race) {
        super(name, age, 16, "Miaw !");
        this.race = race;
    }

    public String getRace() {
        return race;
    }

    @Override
    public String toString() {
        return this.getName() + " is a "+getClass().getName().substring(3)+", he is " + this.getAge() + " years old";
    }
}