package bo;

public class NavalGrid {
    private Ship[] ships;
    private int cbShips;
    private int size;
    private Coordonnee[] receivedShoots;
    private int cbReceivedShoots;
    private GraphicalGrid gridPlacement;

    public NavalGrid(int size, int[] nbShips) {
        if (size < 0 || size > 26) {
            throw new IllegalArgumentException("Size must be between 0 and 26");
        }

        this.size = size;
        this.receivedShoots = new Coordonnee[size * size];
        this.ships = new Ship[nbShips.length];
        this.cbReceivedShoots = 0;
        this.cbShips = 0;
    }

    public NavalGrid(int size, int nbShips) {
        if (size < 0 || size > 26) {
            throw new IllegalArgumentException("Size must be between 0 and 26");
        }

        this.receivedShoots = new Coordonnee[size * size];
        this.ships = new Ship[nbShips];
        this.cbReceivedShoots = 0;
        this.size = size;
        this.cbShips = 0;
    }

    @Override
    public String toString() {
        StringBuffer str = new StringBuffer("   ");
		for (int i = 0; i < this.size; i++) {
			str.append((char) (65 + i)).append(" ");
		}
		str.append("\n");
		for (int i = 0; i < this.size; i++) {
			if (i < 9) {
				str.append(" ");
			}
			str.append(i + 1);
			for (int j = 0; j < this.size; j++) {
				str.append(" ").append(".");
			}
			str.append("\n");
		}

		int indDebut, ind, indFin, indSuivant;
		for (int i = 0; i < ships.length; i++) {
			try {
				if ((ships[i].getStarting().getRow() == ships[i].getEnding().getRow())) {
					ind = i;
					indDebut = (ships[ind].getStarting().getRow() + 1) * (this.size * 2 + 3) + 4
							+ ships[ind].getStarting().getColumn() * 2;
					indFin = (ships[ind].getEnding().getRow() + 1) * (this.size * 2 + 3) + 4
							+ ships[ind].getEnding().getColumn() * 2;
					for (int j = indDebut; j <= indFin; j += 2) {
						str.setCharAt(j, '#');
					}
				} else {
					ind = i;
					indSuivant = ((ships[ind].getStarting().getRow() + 1) + 1) * (this.size * 2 + 3) + 4
							+ (ships[ind].getStarting().getColumn()) * 2;
					indDebut = (ships[ind].getStarting().getRow() + 1) * (this.size * 2 + 3) + 4
							+ ships[ind].getStarting().getColumn() * 2;
					indFin = (ships[ind].getEnding().getRow() + 1) * (this.size * 2 + 3) + 4
							+ ships[ind].getEnding().getColumn() * 2;
					for (int j = indDebut; j <= indFin; j += (indSuivant - indDebut)) {
						str.setCharAt(j, '#');
					}
				}
			} catch (NullPointerException e) {
				break;

			}

		}

		for (int i = 0; i < cbReceivedShoots; i++) {
			try {
				int j = (receivedShoots[i].getRow() + 1) * (this.size * 2 + 3) + 4 + receivedShoots[i].getColumn() * 2;
				if (str.charAt(j) == '#')
					str.setCharAt(j, 'X');
				else
					str.setCharAt(j, 'O');

			} catch (StringIndexOutOfBoundsException e) {
				continue;
			}
		}
		return str.toString();
    }

    public int getSize() {
        return this.size;
    }

    public boolean addShip(Ship ship) {
        if (this.isInGrid(ship.getEnding()) && this.isInGrid(ship.getStarting())) {
			for (int i = 0; i < this.cbShips; i++) {
				if (this.ships[i].touch(ship) || this.ships[i].overlaps(ship)) {
					System.out.println("\n" + ship + " touching or overlaping of " + this.ships[i] + " has failed");
					return false;
				}
			}

			this.ships[cbShips] = ship;
			cbShips++;
			System.out.println("\n" + ship + " success");
			return true;

		}
		System.out.println("\n" + ship + " is out of the grid");
		return false;
    }

    public int getShip() {
        return ships.length;
    }

    public void placementAuto(int[] shipSizes) {
        int i = 0;
		if (shipSizes.length > this.ships.length) {
			System.out.println("The grid must contains a maximum of " + this.ships.length + " ships");
		} else {
            while (i < shipSizes.length) {
                boolean isVertical = Math.random() < 0.5;
                int StartingRow = 0;
                int startingColumn = 0;
                if (isVertical) {
                    StartingRow = (int) ((this.size - shipSizes[i] + 1) * Math.random());
                    startingColumn = (int) ((this.size) * Math.random());
                } else {
                    StartingRow = (int) ((this.size) * Math.random());
                    startingColumn = (int) ((this.size - shipSizes[i] + 1) * Math.random());
                }

                Coordonnee startingCoords = new Coordonnee(StartingRow, startingColumn);
                Ship n = new Ship(startingCoords, shipSizes[i], isVertical);
                if (addShip(n)) {
                    i++;
                }
            }
        }
    }

    private boolean isInGrid(Coordonnee coords) {
        return (coords.getColumn() < this.size && coords.getRow() < this.size);
    }

    private boolean isInShootsReceived(Coordonnee coords) {
        if (isInGrid(coords)) {
            if (cbReceivedShoots != 0) {
                for (int i = 0; i < cbReceivedShoots; i++) {
                    if (this.receivedShoots[i].equals(coords)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    private boolean addIntoShootsReceived(Coordonnee coords) {
		if (this.isInShootsReceived(coords)) {
            return false;
        }

		receivedShoots[cbReceivedShoots] = coords;
		cbReceivedShoots++;
		return true;
    }

    public boolean receiveShoot(Coordonnee coords) {
        boolean shoot = addIntoShootsReceived(coords);
        boolean touch = false;

        if (shoot) {
            int i = 0;
            while (i < cbShips && !touch) {
				if (ships[i].receiveShoot(coords)) {
                    touch = true;
                }
                i++;
            }
        }

        return touch;
    }

    public boolean isTouched(Coordonnee coords) {
		for (int i = 0; i < this.cbShips; i++) {
			if (this.ships[i].isTouched(coords))
				return true;
		}

		return false;
    }

    public boolean isMissed(Coordonnee coords) {
        return !this.isTouched(coords);
    }

    public boolean isSunk(Coordonnee c) {
		for (int i = 0; i < this.cbShips; i++) {
			if (this.ships[i].isTouched(c) && this.ships[i].isSunk()) {
				System.out.println(this.ships[i] + " was sunk because of the shoot at " + c);
				return true;
			}
		}
		return false;
	}

    public boolean loose() {
        for (int i = 0; i < this.cbShips; i++) {
            if (!(this.ships[i].isSunk())) {
                return false;
            }
        }

        System.out.println("GAME OVER !");
		return true;
    }
}
