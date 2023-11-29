package Facade;

import bo.Pokemon;
import bo.Tournament;
import bo.Game;
import exceptions.ErrorAddException;
import exceptions.LimitMaxException;
import exceptions.NbFighterException;
import exceptions.TooMuchFighterException;

public class Facade {
    private Tournament tournament;

    public Facade() {

    }

    public void createTournament(String name, int maxPokemon) {
        try {
            this.tournament = new Tournament(name, maxPokemon);
        } catch (NbFighterException e) {
            System.out.println(e.getMessage());
            System.exit(-1);
        }
    }

    public void addPokemon(String name, int lifeLevel, int powerLevel, String shoutBattle, String shoutVictory, String shoutDefeat){
        try {
            tournament.addPokemon(new Pokemon(name,lifeLevel,powerLevel,shoutBattle,shoutVictory,shoutDefeat));
        } catch (ErrorAddException e) {
            System.out.println(e.getMessage());
        } catch (TooMuchFighterException e) {
            System.out.println(e.getMessage());
        }
    }

    public void go() {
        Game game = new Game(tournament);
        game.start();
    }
}
