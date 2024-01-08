package bo;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;

public class ShipPlacementWindow extends JFrame {
    private JPanel contentPane;
    private JPanel topPanel;
    private GraphicalGrid placementGrid;
    private int allShipsPlacedNbr = 0;
    private int size;
    private int[] ships;
    private boolean isVertical = true;

    public ShipPlacementWindow() {
        this("Player Name", 10, new int[] { 2, 3, 3, 4, 5 }, new GraphicalNavalGrid(10));
    }

    public ShipPlacementWindow(String name, int size, int[] ships, GraphicalNavalGrid grid) {
        this.ships = ships;
        this.placementGrid = new GraphicalGrid(size);
        this.placementGrid.setClickActive(false);
        this.size = size;

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setBounds(100, 100, (int) (size * 80), (int) (size * 40));
        contentPane = new JPanel();
        contentPane.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1;
        gbc.weighty = 0.75;
        gbc.fill = GridBagConstraints.BOTH;

        setContentPane(contentPane);

        topPanel = new JPanel();
        topPanel.setLayout(new GridLayout(1, 2));
        contentPane.add(topPanel, gbc);

        JPanel panel = getPlacementGrid();
        panel.setBorder(BorderFactory.createTitledBorder(null, "Placement Grid", TitledBorder.CENTER, TitledBorder.DEFAULT_JUSTIFICATION));
        topPanel.add(panel);

        JButton rotateButton = new JButton("Rotate Ship Horizontaly");
        rotateButton.addActionListener(e -> {
            isVertical = !isVertical;
            rotateButton.setText(!isVertical ? "Rotate Ship Verticaly" : "Rotate Ship Horizontaly");
        });
        gbc.gridy = 1;
        gbc.weighty = 0.25;
        gbc.insets = new Insets(10, 10, 10, 10);
        contentPane.add(rotateButton, gbc);

        placeShips(grid);
    }

	private String getShipName(int size) {
		final Map<Integer, String> ships = new HashMap<Integer, String>() {{
			put(5, "Porte-Avions");
			put(4, "Croisseur");
			put(3, "Contre-Torpilleurs");
			put(2, "Torpilleur");
		}};
		return ships.get(size);
	}

    private void placeShips(GraphicalNavalGrid grid) {
        JPanel shipsPanelContainer = new JPanel();
        shipsPanelContainer.setLayout(new GridLayout(1, 1));
        shipsPanelContainer.setBorder(BorderFactory.createTitledBorder(null, "Available Ship(s)", TitledBorder.CENTER, TitledBorder.DEFAULT_JUSTIFICATION));

        JPanel shipsPanel = new JPanel();
        shipsPanel.setLayout(new GridLayout(ships.length, 1));
        shipsPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        shipsPanelContainer.add(shipsPanel);

        for (int ship : ships) {
            JButton shipButton = new JButton(getShipName(ship) + " (" + ship + ")");
            shipButton.addActionListener(e -> {
                new Thread() {
                    public void run() {
                        Coordonnee coords = placementGrid.getSelectedCoords();

                        Ship n = new Ship(coords, ship, isVertical);
                        if (grid.addShip(n)) {
                            placementGrid.setColor(n.getStarting(), n.getEnding(), Color.GRAY);
                            ((JButton) e.getSource()).setEnabled(false);
                            allShipsPlacedNbr++;
                        } else {
                            JOptionPane.showMessageDialog(null, "Impossible de placer le bateau ici");
                        }
                    }
                }.start();
            });
            shipsPanel.add(shipButton);
        }

        topPanel.add(shipsPanelContainer);
    }

    public boolean isAllShipsPlaced() {
        return allShipsPlacedNbr == ships.length;
    }

    public GraphicalGrid getPlacementGrid() {
        return placementGrid;
    }
}
