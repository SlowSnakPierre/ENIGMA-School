package bo;

public class Animal {
    private String name;
    private int age;
    private int ageMax;
    private String shout;

    public Animal(String name, int age, int ageMax, String shout) {
        this.name = name;
        this.age = age;
        this.ageMax = ageMax;
        this.shout = shout;
    }

    public int getAge() {
        return this.age;
    }

    public String getName() {
        return this.name;
    }

    public int getAgeMax() {
        return this.ageMax;
    }

    public String getShout() {
        return this.shout;
    }

    public String eat() {
        return this.name + ": " + this.shout;
    }

    public boolean getOlder() {
        this.age++;

        if (this.age > this.ageMax) {
            System.out.println(this.name+" est mort !");
            return false;
        }

        return true;
    }
}
