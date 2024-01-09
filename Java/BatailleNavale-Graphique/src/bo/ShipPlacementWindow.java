package bo;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;

public class ShipPlacementWindow extends JFrame {
    final private JPanel topPanel;
    final private GraphicalGrid placementGrid;
    private int allShipsPlacedNbr = 0;
    final private int[] ships;
    private boolean isVertical = true;

    public ShipPlacementWindow(int size, int[] ships, GraphicalNavalGrid grid) {
        this.ships = ships;
        this.placementGrid = new GraphicalGrid(size);
        this.placementGrid.setClickActive(false);

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setBounds(100, 100, size * 80,size * 40 + 50);
        JPanel contentPane = new JPanel();
        contentPane.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1;
        gbc.weighty = 0.9;
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
        gbc.weighty = 0.1;
        gbc.insets = new Insets(10, 10, 10, 10);
        contentPane.add(rotateButton, gbc);

        placeShips(grid);
    }

	private String getShipName(int size) {
		final Map<Integer, String> ships = new HashMap<>() {{
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
        GridLayout layout = new GridLayout(ships.length, 1);
        layout.setVgap(10);
        shipsPanel.setLayout(layout);
        shipsPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        shipsPanelContainer.add(shipsPanel);

        for (int ship : ships) {
            JButton shipButton = new JButton(getShipName(ship) + " (" + ship + ")");
            shipButton.addActionListener(e -> new Thread(() -> {
                Coordonnee coords = placementGrid.getSelectedCoords();

                Ship n = new Ship(coords, ship, isVertical);
                if (grid.addShip(n)) {
                    placementGrid.setColor(n.getStarting(), n.getEnding(), Color.GRAY);
                    ((JButton) e.getSource()).setEnabled(false);
                    allShipsPlacedNbr++;
                } else {
                    JOptionPane.showMessageDialog(null, "Impossible de placer le bateau ici");
                }
            }).start());
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
