package bo;

public class Pokemon {
    private String name;
    private int lifeLevel;
    private int powerLevel;
    private String shoutBattle;
    private String shoutVictory;
    private String shoutDefeat;

    public Pokemon(String name, int lifeLevel, int powerLevel, String shoutBattle, String shoutVictory, String shoutDefeat) {
        this.name = name;
        this.lifeLevel = lifeLevel;
        this.powerLevel = powerLevel;
        this.shoutBattle = shoutBattle;
        this.shoutVictory = shoutVictory;
        this.shoutDefeat = shoutDefeat;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getLifeLevel() {
        return lifeLevel;
    }

    public void setLifeLevel(int lifeLevel) {
        this.lifeLevel = lifeLevel;
    }

    public int getPowerLevel() {
        return powerLevel;
    }

    public void setPowerLevel(int powerLevel) {
        this.powerLevel = powerLevel;
    }

    public String getShoutBattle() {
        return shoutBattle;
    }

    public void setShoutBattle(String shoutBattle) {
        this.shoutBattle = shoutBattle;
    }

    public String getShoutVictory() {
        return shoutVictory;
    }

    public void setShoutVictory(String shoutVictory) {
        this.shoutVictory = shoutVictory;
    }

    public String getShoutDefeat() {
        return shoutDefeat;
    }

    public void setShoutDefeat(String shoutDefeat) {
        this.shoutDefeat = shoutDefeat;
    }

    @Override
    public String toString() {
        return name;
    }
}
