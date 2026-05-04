import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

class Node {
    int id;
    double x, y;

    public Node(int id, double x, double y) {
        this.id = id;
        this.x = x;
        this.y = y;
    }
}

public class SimpleGUI extends JFrame {
    private List<Node> nodes = new ArrayList<>();
    private JPanel canvas;

    public SimpleGUI() {
        setTitle("GraphVisualizer - Proof of Concept");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        JButton btnSimulate = new JButton("Symuluj wczytanie danych z C");
        add(btnSimulate, BorderLayout.NORTH);

        canvas = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                Graphics2D g2d = (Graphics2D) g;
                g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

                g2d.setColor(Color.BLUE);
                for (Node n : nodes) {
                    int radius = 20;
                    int drawX = (int) n.x - radius / 2;
                    int drawY = (int) n.y - radius / 2;
                    
                    g2d.fillOval(drawX, drawY, radius, radius);
                    g2d.setColor(Color.BLACK);
                    g2d.drawString("ID: " + n.id, drawX, drawY - 5);
                    g2d.setColor(Color.BLUE);
                }
            }
        };
        canvas.setBackground(Color.WHITE);
        add(canvas, BorderLayout.CENTER);

        btnSimulate.addActionListener(e -> {
            nodes.clear();
            nodes.add(new Node(1, 100, 100));
            nodes.add(new Node(2, 400, 150));
            nodes.add(new Node(3, 200, 400));
            nodes.add(new Node(4, 600, 300));
            
            canvas.repaint();
        });
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            new SimpleGUI().setVisible(true);
        });
    }
}
