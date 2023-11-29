package go;

import bo.*;

import javax.swing.*;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

@SuppressWarnings("DuplicatedCode")
public class Main {
    private Player player1, player2;
    private int GRID_SIZE;
    private JFrame frmSeaBattle;

    private JTextField textField;
    private JTextField textField_1;
    private JTextField textField_2;
    private final ButtonGroup buttonGroup_P1 = new ButtonGroup();
    private final ButtonGroup buttonGroup_P2 = new ButtonGroup();

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    Main window = new Main();
                    window.frmSeaBattle.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    private void startGame() {
        new Thread() {
            public void run() {
                if ((player1 == null) || (player2 == null)) {
                    JOptionPane.showMessageDialog(frmSeaBattle, " Please give a player a name \n and choose a type ");
                    return;
                }
                player1.playWith(player2);
            }
        }.start();
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
		frmSeaBattle.setBounds(0, 0, 265, 450);
		centreWindow(frmSeaBattle);
		frmSeaBattle.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmSeaBattle.getContentPane().setLayout(null);

		JPanel panel1 = new JPanel();
		panel1.setBounds(0, 1, 250, 33);
		panel1.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		frmSeaBattle.getContentPane().add(panel1);
		panel1.setLayout(new BoxLayout(panel1, BoxLayout.X_AXIS));
		JLabel lblGridSize = new JLabel("Grid Size : ");
		lblGridSize.setFont(new Font("Dialog", Font.BOLD, 13));
		panel1.add(lblGridSize);
		textField = new JTextField();
		panel1.add(textField);
		textField.setColumns(10);

		JPanel panel2 = new JPanel();
		panel2.setBounds(0, 41, 250, 320);
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
		textField_1 = new JTextField();
		panel.add(textField_1);
		textField_1.setColumns(10);
		JRadioButton rdbtP1Graphical = new JRadioButton("Graphical Player");
		buttonGroup_P1.add(rdbtP1Graphical);
		rdbtP1Graphical.setSelected(true);
		rdbtP1Graphical.setFont(new Font("Dialog", Font.BOLD, 13));
		panel_Player1.add(rdbtP1Graphical);
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
		textField_2 = new JTextField();
		panel_1.add(textField_2);
		textField_2.setColumns(10);

		JRadioButton rdbtP2Graphical = new JRadioButton("Graphical Player");
		rdbtP2Graphical.setFont(new Font("Dialog", Font.BOLD, 13));
		buttonGroup_P2.add(rdbtP2Graphical);
		panel_Player2.add(rdbtP2Graphical);

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
		panel3.setBounds(20, 360, 280, 53);
		frmSeaBattle.getContentPane().add(panel3);
		panel3.setLayout(null);
		JButton StartGameBtn = new JButton("Start Game");
        StartGameBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                EventQueue.invokeLater(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            GRID_SIZE = Integer.parseInt(textField.getText());
                        } catch (NumberFormatException e) {
                            JOptionPane.showMessageDialog(frmSeaBattle, " Please enter a valid number ! ");
                            return;
                        }

                        if ((GRID_SIZE < 5 || GRID_SIZE > 26)) {
                            JOptionPane.showMessageDialog(frmSeaBattle, " The grid size must be between 5 and 26 ! ");
                            return;
                        }

                        int[] tabNav = { 2, 3, 3, 4, 5 };
                        if (GRID_SIZE <= 10) {
                            tabNav = new int[] { 2, 3, 3 };
                        }

                        if (rdbtP1Graphical.isSelected()) {
							PlayerWindow window = new PlayerWindow(textField_1.getText(), GRID_SIZE);
							window.getDefendingGrid().placementAuto(tabNav);
							centreWindow(window);
							if (textField_1.getText().compareTo("")==0) {
								window.setTitle("Sea Battle : Player 1");
							} else {
								window.setTitle("Sea Battle : " + textField_1.getText());
							}
							window.setVisible(true);
							player1 = new GraphicalPlayer(window.getDefendingGrid(), window.getShootingGrid(), textField_1.getText());
						} else if (rdbtP1Texte.isSelected()) {
							NavalGrid P1Grid = new NavalGrid(GRID_SIZE, tabNav);
							P1Grid.placementAuto(tabNav);
							if (textField_1.getText().compareTo("")==0) {
								player1 = new TextualPlayer(P1Grid, "Player 1");
							} else {
								player1 = new TextualPlayer(P1Grid, textField_1.getText());
							}
						} else if (rdbtP1Auto.isSelected()) {
							NavalGrid G1 = new NavalGrid(GRID_SIZE, tabNav);
							G1.placementAuto(tabNav);
							if (textField_1.getText().compareTo("")==0) {
								player1 = new AutoPlayer(G1, "Player 1 (Auto)");
							} else {
								player1 = new AutoPlayer(G1, textField_1.getText());
							}
						}

                        if (rdbtP2Graphical.isSelected()) {
							PlayerWindow window2 = new PlayerWindow(textField_2.getText(), GRID_SIZE);
							window2.getDefendingGrid().placementAuto(tabNav);
							centreWindow(window2);
							if (textField_2.getText().compareTo("")==0) {
								window2.setTitle("Sea Battle : Player 2");
							} else {
								window2.setTitle("Sea Battle : " + textField_2.getText());
							}
							window2.setVisible(true);
							player2 = new GraphicalPlayer(window2.getDefendingGrid(), window2.getShootingGrid(), textField_2.getText());
						} else if (rdbtP2Texte.isSelected()) {
							NavalGrid P2Grid = new NavalGrid(GRID_SIZE, tabNav);
							P2Grid.placementAuto(tabNav);
							if (textField_2.getText().compareTo("")==0) {
								player2 = new TextualPlayer(P2Grid, "Player 2");
							} else {
								player2 = new TextualPlayer(P2Grid, textField_2.getText());
							}
						} else if (rdbtP2Auto.isSelected()) {
							NavalGrid G2 = new NavalGrid(GRID_SIZE, tabNav);
							G2.placementAuto(tabNav);
							if (textField_2.getText().compareTo("")==0) {
								player2 = new AutoPlayer(G2, "Player 2 (Auto)");
							} else {
								player2 = new AutoPlayer(G2, textField_2.getText());
							}
						}

						startGame();
					}
                });
            }
        });

		StartGameBtn.setFont(new Font("Dialog", Font.BOLD, 13));
		StartGameBtn.setBounds(27, 12, 135, 27);
		panel3.add(StartGameBtn);
    }
}