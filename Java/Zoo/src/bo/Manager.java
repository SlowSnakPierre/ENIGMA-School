package bo;

public class Manager {
    private String name;
    private int ysSeniority;

    public Manager(String name, int ysSeniority) {
        this.name = name;
        this.ysSeniority = ysSeniority;
    }

    public int getYsSeniority() {
        return ysSeniority;
    }

    public void setYsSeniority(int ysSeniority) {
        this.ysSeniority = ysSeniority;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "I'm the manager " + name + ", I have " + ysSeniority + " years of seniority";
    }
}
