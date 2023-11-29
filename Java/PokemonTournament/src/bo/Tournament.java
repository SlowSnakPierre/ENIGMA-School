package bo;

import exceptions.ErrorAddException;
import exceptions.NbFighterException;
import exceptions.TooMuchFighterException;

import java.util.ArrayList;

import static bo.Game.powerOfTwoBitwise;

public class Tournament {
    private String name;
    private int maxPokemon;
    private ArrayList<Pokemon> pokemons;

    public Tournament(String name, int maxPokemon) throws NbFighterException {
        this.name = name;
        if (!powerOfTwoBitwise(maxPokemon)) {
            throw new NbFighterException();
        }
        this.maxPokemon = maxPokemon;
        this.pokemons = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getMaxPokemon() {
        return maxPokemon;
    }

    public void setMaxPokemon(int maxPokemon) {
        this.maxPokemon = maxPokemon;
    }

    public ArrayList<Pokemon> getPokemons() {
        return pokemons;
    }

    public boolean addPokemon(Pokemon pokemon) throws TooMuchFighterException, ErrorAddException {
        boolean retour = false;

        if (pokemons.size() == this.getMaxPokemon()) {
            throw new TooMuchFighterException();
        } else if (pokemons.add(pokemon)) {
            System.out.println("Pokemon : " + pokemon.getName() + " ajouté");
            retour = true;
        } else {
            throw new ErrorAddException();
        }

        return retour;
    }
}
