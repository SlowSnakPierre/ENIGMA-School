package go;

import Facade.Facade;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        String[] LooseMessages = new String[5];
        LooseMessages[0] = "Je suis un looser";
        LooseMessages[1] = "Je suis un nul";
        LooseMessages[2] = "Je suis perdant";
        LooseMessages[3] = "Je suis guez";
        LooseMessages[4] = "Je suis naze";

        String[] VictoryMessages = new String[5];
        VictoryMessages[0] = "Je suis un Dieux";
        VictoryMessages[1] = "Je suis un Gagnant";
        VictoryMessages[2] = "Je suis trop chaud";
        VictoryMessages[3] = "Je suis trop fort";
        VictoryMessages[4] = "Je suis le meilleur";


        Scanner sc = new Scanner(System.in);

        System.out.println("Veuillez saisir le nom du tournoi : ");
        String nomTournoi = sc.nextLine();
        System.out.println();

        System.out.println("Veuillez saisir le nombre de participant : ");
        int nbParticipant = sc.nextInt();
        sc.nextLine();
        System.out.println();

        Facade facade = new Facade();
        facade.createTournament(nomTournoi, nbParticipant);

        for(int i = 0 ; i < nbParticipant ; i++){
            System.out.println("Veuillez saisir le nom du pokemon :");
            String name = sc.nextLine();
            System.out.println("Veuillez saisir le niveau de vie du pokemon :");
            int lifeLevel= 100;//sc.nextInt();
            //sc.nextLine();
            //System.out.println("Veuillez saisir le niveau de pouvoir du Pokemon :");
            int powerLevel = new Random().nextInt((10 - 1) + 1) + 1; //sc.nextInt();
            System.out.println("Niveau de pouvoir du Pokémon : " + powerLevel);
            //sc.nextLine();
            System.out.println("Veuillez saisir le cris de combat :");
            String shoutBattle = sc.nextLine();
            System.out.println("Veuillez saisir le cris de victoire :");
            String shoutVictory = getRandom(VictoryMessages);//sc.nextLine();
            System.out.println(shoutVictory);
            System.out.println("Veuillez saisir le cris de défaite :");
            String shoutLoose = getRandom(LooseMessages);//sc.nextLine();
            System.out.println(shoutLoose);
            facade.addPokemon(name,lifeLevel,powerLevel,shoutBattle,shoutVictory,shoutLoose);
            System.out.println();
        }

        facade.go();
    }

    public static String getRandom(String[] array) {
        int rnd = new Random().nextInt(array.length);
        return array[rnd];
    }
}