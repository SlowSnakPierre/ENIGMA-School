package go;

import bo.*;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;

@SuppressWarnings("DuplicatedCode")
public class Main {
    private Player player1, player2;
    private final int GRID_SIZE = 10;
	final int[] tabNav = { 2, 3, 3, 4, 5 };
    private JFrame frmSeaBattle;
    private JTextField textField_P1;
    private JTextField textField_P2;
    private final ButtonGroup buttonGroup_P1 = new ButtonGroup();
    private final ButtonGroup buttonGroup_P2 = new ButtonGroup();

    public static void main(String[] args) {
        try {
            Main window = new Main();
            window.frmSeaBattle.setVisible(true);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void startGame() {
        new Thread(() -> {
            if ((player1 == null) || (player2 == null)) {
                JOptionPane.showMessageDialog(frmSeaBattle, " Please give a player a name \n and choose a type ("+((player1 == null) ? "Player 1" : "Player 2")+" is missing)");
                return;
            }
            frmSeaBattle.setVisible(false);
            player1.playWith(player2);
        }).start();
    }

    public Main() {
        initialize();
    }

	public static void centreWindow(Window frame) {
		Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
		int x = (int) ((dimension.getWidth() - frame.getWidth()) / 2);
		int y = (int) ((dimension.getHeight() - frame.getHeight()) / 2);
		frame.setLocation(x, y);
	}

    private void initialize() {
		frmSeaBattle = new JFrame();
		frmSeaBattle.setResizable(false);
		frmSeaBattle.setTitle("Sea Battle");
		frmSeaBattle.setBounds(0, 0, 265, 400);
		centreWindow(frmSeaBattle);
		frmSeaBattle.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmSeaBattle.getContentPane().setLayout(null);

		JPanel panel2 = new JPanel();
		panel2.setBounds(0, 1, 250, 320);
		frmSeaBattle.getContentPane().add(panel2);
		panel2.setLayout(new GridLayout(2,0,0,0));
		JPanel panel_Player1 = new JPanel();

		panel_Player1.setBorder(new TitledBorder(UIManager.getBorder("TitledBorder.border"), "Player 1",
		TitledBorder.LEADING, TitledBorder.TOP, null));
		panel2.add(panel_Player1);
		panel_Player1.setLayout(new GridLayout(5, 0, 0, 0));
		JPanel panel = new JPanel();
		panel_Player1.add(panel);
		panel.setLayout(new BoxLayout(panel, BoxLayout.X_AXIS));
		JLabel lblNom = new JLabel("Name : ");
		lblNom.setFont(new Font("Dialog", Font.BOLD, 13));
		panel.add(lblNom);
		textField_P1 = new JTextField();
		panel.add(textField_P1);
		textField_P1.setColumns(10);

		JRadioButton rdbtP1Graphical = new JRadioButton("Graphical Player (Manual)");
		buttonGroup_P1.add(rdbtP1Graphical);
		rdbtP1Graphical.setSelected(true);
		rdbtP1Graphical.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_Player1.add(rdbtP1Graphical);

		JRadioButton rdbtP1GraphicalAuto = new JRadioButton("Graphical Player (Auto)");
		buttonGroup_P1.add(rdbtP1GraphicalAuto);
		rdbtP1GraphicalAuto.setSelected(true);
		rdbtP1GraphicalAuto.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_Player1.add(rdbtP1GraphicalAuto);

		JRadioButton rdbtP1Texte = new JRadioButton("Textual Player");
		buttonGroup_P1.add(rdbtP1Texte);
		rdbtP1Texte.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_Player1.add(rdbtP1Texte);
		JRadioButton rdbtP1Auto = new JRadioButton("Automatic Player");
		buttonGroup_P1.add(rdbtP1Auto);
		rdbtP1Auto.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_Player1.add(rdbtP1Auto);
		JPanel panel_Player2 = new JPanel();

		panel_Player2.setBorder(BorderFactory.createTitledBorder("Player 2"));
		panel2.add(panel_Player2);
		panel_Player2.setLayout(new GridLayout(5, 0, 0, 0));
		JPanel panel_1 = new JPanel();
		panel_Player2.add(panel_1);
		panel_1.setLayout(new BoxLayout(panel_1, BoxLayout.X_AXIS));
		JLabel lblNewLabel = new JLabel("Name : ");
		lblNewLabel.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_1.add(lblNewLabel);
		textField_P2 = new JTextField();
		panel_1.add(textField_P2);
		textField_P2.setColumns(10);

		JRadioButton rdbtP2Graphical = new JRadioButton("Graphical Player (Manual)");
		rdbtP2Graphical.setFont(new Font("Dialog", Font.BOLD, 13));
		buttonGroup_P2.add(rdbtP2Graphical);
		panel_Player2.add(rdbtP2Graphical);

		JRadioButton rdbtP2GraphicalAuto = new JRadioButton("Graphical Player (Auto)");
		rdbtP2GraphicalAuto.setFont(new Font("Dialog", Font.BOLD, 13));
		buttonGroup_P2.add(rdbtP2GraphicalAuto);
		panel_Player2.add(rdbtP2GraphicalAuto);

		JRadioButton rdbtP2Texte = new JRadioButton("Textual Player");
		rdbtP2Texte.setFont(new Font("Dialog", Font.BOLD, 13));
		buttonGroup_P2.add(rdbtP2Texte);
		panel_Player2.add(rdbtP2Texte);

		JRadioButton rdbtP2Auto = new JRadioButton("Automatic Player");
		rdbtP2Auto.setFont(new Font("Dialog", Font.BOLD, 13));
		buttonGroup_P2.add(rdbtP2Auto);
		panel_Player2.add(rdbtP2Auto);
		rdbtP2Auto.setSelected(true);

		JPanel panel3 = new JPanel();
		panel3.setBounds(20, 315, 280, 53);
		frmSeaBattle.getContentPane().add(panel3);
		panel3.setLayout(null);
		JButton StartGameBtn = new JButton("Start Game");
        StartGameBtn.addActionListener(e -> EventQueue.invokeLater(() -> {
            String p1Name = textField_P1.getText().compareTo("")==0 ? "Player 1" : textField_P1.getText();
            String p2Name = textField_P2.getText().compareTo("")==0 ? "Player 2" : textField_P2.getText();

            if (rdbtP1Graphical.isSelected()) {
                PlayerWindow window = new PlayerWindow(GRID_SIZE);
                ShipPlacementWindow placementWindow = new ShipPlacementWindow(GRID_SIZE, tabNav, window.getDefendingGrid());
                placementWindow.setTitle("Sea Battle : " + p1Name + " Waiting for placement");
                centreWindow(placementWindow);
                placementWindow.setVisible(true);

                new SwingWorker<Void, Void>() {
                    @Override
                    protected Void doInBackground() {
                        while (!placementWindow.isAllShipsPlaced()) {
                            try {
                                Thread.sleep(1000);
                            } catch (InterruptedException ex) {
                                ex.printStackTrace();
                            }
                        }
                        return null;
                    }

                    @Override
                    protected void done() {
                        placementWindow.setVisible(false);
                        centreWindow(window);
                        window.setTitle("Sea Battle : " + p1Name);
                        window.setVisible(true);
                        player1 = new GraphicalPlayer(window.getDefendingGrid(), window.getShootingGrid(), p1Name);

                        if (rdbtP2Graphical.isSelected()) {
                            PlayerWindow window2 = new PlayerWindow(GRID_SIZE);
                            ShipPlacementWindow placementWindow = new ShipPlacementWindow(GRID_SIZE, tabNav, window2.getDefendingGrid());
                            placementWindow.setTitle("Sea Battle : " + p2Name + " Waiting for placement");
                            centreWindow(placementWindow);
                            placementWindow.setVisible(true);

                            new SwingWorker<Void, Void>() {
                                @Override
                                protected Void doInBackground() {
                                    while (!placementWindow.isAllShipsPlaced()) {
                                        try {
                                            Thread.sleep(1000);
                                        } catch (InterruptedException ex) {
                                            ex.printStackTrace();
                                        }
                                    }
                                    return null;
                                }

                                @Override
                                protected void done() {
                                    placementWindow.setVisible(false);
                                    centreWindow(window2);
                                    window2.setTitle("Sea Battle : " + p2Name);
                                    window2.setVisible(true);
                                    player2 = new GraphicalPlayer(window2.getDefendingGrid(), window2.getShootingGrid(), p2Name);
                                    startGame();
                                }
                            }.execute();
                        } else if (rdbtP2GraphicalAuto.isSelected()) {
                            PlayerWindow window2 = new PlayerWindow(GRID_SIZE);
                            window2.getDefendingGrid().placementAuto(tabNav);
                            centreWindow(window2);
                            window2.setTitle("Sea Battle : " + p2Name);
                            window2.setVisible(true);
                            player2 = new GraphicalPlayer(window2.getDefendingGrid(), window2.getShootingGrid(), p2Name);
                            startGame();
                        } else if (rdbtP2Texte.isSelected()) {
                            NavalGrid P2Grid = new NavalGrid(GRID_SIZE, tabNav);
                            P2Grid.placementAuto(tabNav);
                            player2 = new TextualPlayer(P2Grid, p2Name);
                            startGame();
                        } else if (rdbtP2Auto.isSelected()) {
                            NavalGrid G2 = new NavalGrid(GRID_SIZE, tabNav);
                            G2.placementAuto(tabNav);
                            player2 = new AutoPlayer(G2, p2Name);
                            startGame();
                        }
                    }
                }.execute();
            } else if (rdbtP1GraphicalAuto.isSelected()) {
                PlayerWindow window = new PlayerWindow(GRID_SIZE);
                window.getDefendingGrid().placementAuto(tabNav);
                centreWindow(window);
                window.setTitle("Sea Battle : " + p2Name);
                window.setVisible(true);
                player1 = new GraphicalPlayer(window.getDefendingGrid(), window.getShootingGrid(), p1Name);
            } else if (rdbtP1Texte.isSelected()) {
                NavalGrid P1Grid = new NavalGrid(GRID_SIZE, tabNav);
                P1Grid.placementAuto(tabNav);
                player1 = new TextualPlayer(P1Grid, p1Name);
            } else if (rdbtP1Auto.isSelected()) {
                NavalGrid G1 = new NavalGrid(GRID_SIZE, tabNav);
                G1.placementAuto(tabNav);
                player1 = new AutoPlayer(G1, p1Name);
            }

            if (!rdbtP1Graphical.isSelected()) {
                if (rdbtP2Graphical.isSelected()) {
                    PlayerWindow window2 = new PlayerWindow(GRID_SIZE);
                    ShipPlacementWindow placementWindow = new ShipPlacementWindow(GRID_SIZE, tabNav, window2.getDefendingGrid());
                    placementWindow.setTitle("Sea Battle : " + p2Name + " Waiting for placement");
                    centreWindow(placementWindow);
                    placementWindow.setVisible(true);

                    new SwingWorker<Void, Void>() {
                        @Override
                        protected Void doInBackground() {
                            while (!placementWindow.isAllShipsPlaced()) {
                                try {
                                    Thread.sleep(1000);
                                } catch (InterruptedException ex) {
                                    ex.printStackTrace();
                                }
                            }
                            return null;
                        }

                        @Override
                        protected void done() {
                            placementWindow.setVisible(false);
                            centreWindow(window2);
                            window2.setTitle("Sea Battle : " + p2Name);
                            window2.setVisible(true);
                            player2 = new GraphicalPlayer(window2.getDefendingGrid(), window2.getShootingGrid(), p2Name);
                            startGame();
                        }
                    }.execute();
                } else if (rdbtP2GraphicalAuto.isSelected()) {
                    PlayerWindow window2 = new PlayerWindow(GRID_SIZE);
                    window2.getDefendingGrid().placementAuto(tabNav);
                    centreWindow(window2);
                    window2.setTitle("Sea Battle : " + p2Name);
                    window2.setVisible(true);
                    player2 = new GraphicalPlayer(window2.getDefendingGrid(), window2.getShootingGrid(), p2Name);
                    startGame();
                } else if (rdbtP2Texte.isSelected()) {
                    NavalGrid P2Grid = new NavalGrid(GRID_SIZE, tabNav);
                    P2Grid.placementAuto(tabNav);
                    player2 = new TextualPlayer(P2Grid, p2Name);
                    startGame();
                } else if (rdbtP2Auto.isSelected()) {
                    NavalGrid G2 = new NavalGrid(GRID_SIZE, tabNav);
                    G2.placementAuto(tabNav);
                    player2 = new AutoPlayer(G2, p2Name);
                    startGame();
                }
            }
        }));

		StartGameBtn.setFont(new Font("Dialog", Font.BOLD, 13));
		StartGameBtn.setBounds(27, 12, 135, 27);
		panel3.add(StartGameBtn);
    }
}