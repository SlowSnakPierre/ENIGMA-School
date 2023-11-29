package bo;

import exceptions.NbFighterException;
import exceptions.TooMuchFighterException;
import exceptions.ZeroFighterException;

import java.util.ArrayList;
import java.util.Iterator;

public class Game {
    private Tournament tournament;

    public Game(Tournament tournament) {
        this.tournament = tournament;
    }

    public static boolean powerOfTwoBitwise(int n) {
        return (n & n-1) == 0;
    }

    private boolean checkUp() throws TooMuchFighterException, NbFighterException, ZeroFighterException {
        boolean retour = false;

        if (tournament.getMaxPokemon() < tournament.getPokemons().size()) {
            throw new TooMuchFighterException();
        } else if (!powerOfTwoBitwise(tournament.getPokemons().size())) {
            throw new NbFighterException();
        } else if (tournament.getPokemons().isEmpty()) {
            throw new ZeroFighterException();
        } else {
            retour = true;
        }

        return retour;
    }

    public void start() {
        try {
            checkUp();
        } catch (Exception e) {
            System.out.println(e.getMessage());
            System.exit(-1);
        }

        Iterator<Pokemon> it = tournament.getPokemons().iterator();

        while (it.hasNext()) {
            Pokemon pokemon = it.next();
            System.out.println(pokemon.getShoutBattle());
        }

        while (tournament.getPokemons().size() != 1) {
            fight();
        }

        System.out.println(tournament.getPokemons().get(0).getName() + " winner " + tournament.getPokemons().get(0).getShoutVictory());
    }

    public void fight() {
        ArrayList<Pokemon> listOfDeadPokemons = new ArrayList<>();
        for (int i = 0; i < tournament.getPokemons().size(); i+=2) {
            listOfDeadPokemons.add(versus(tournament.getPokemons().get(i), tournament.getPokemons().get(i+1)));
        }
        tournament.getPokemons().removeAll(listOfDeadPokemons);
    }

    private Pokemon versus(Pokemon p1, Pokemon p2) {
        Pokemon pokeASuppr = null;
        int laps = 1;
        System.out.println("-> " + p1.getName() + " vs " + p2.getName());
        while(p1.getLifeLevel() > 0 && p2.getLifeLevel() > 0){
            p1.setLifeLevel(p1.getLifeLevel() - p2.getPowerLevel());
            p2.setLifeLevel(p2.getLifeLevel() - p1.getPowerLevel());
            System.out.println("  -------- LAPS " + laps + " --------");
            System.out.println("  - " + p1.getName() + " life level : " + p1.getLifeLevel());
            System.out.println("  - " + p2.getName() + " life level : " + p2.getLifeLevel());
            laps++;
        }

        if(p1.getLifeLevel() < 0){
            System.out.println("  " + p1.getShoutDefeat());
            pokeASuppr = p1;
        }
        else{
            System.out.println("  " + p2.getShoutDefeat());
            pokeASuppr = p2;
        }
        System.out.println("<- " + p1.getName() + " vs " + p2.getName() + "\r\n");
        return pokeASuppr;
    }
}
