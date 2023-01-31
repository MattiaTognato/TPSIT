
import java.io.*;
import java.net.*;
import java.util.*;

public class WarehouseServer extends Thread {
    public final static int SERVER_PORT = 12345;
    private ServerSocket server;
    private TextFile product_list;
    private HashMap<Long, Product> product_catalog;
    

    public WarehouseServer(int port) throws IOException {
        String line;
        String token[];
        Product product;
        long code;
        int quantity;
        
        server = new ServerSocket(port);
        server.setSoTimeout(1000);
        product_list = new TextFile("prodotti.csv", 'R');
        product_catalog = new HashMap<>();
        try {
            while (true) {
                line = product_list.fromFile();
                token = line.split(",");
                code = Long.parseLong(token[0]);
                quantity = Integer.parseInt(token[2]);
                product = new Product(code, token[1], quantity);
                product_catalog.put(code, product);
            }
        }
        catch (FileException exception) {
            product_list.closeFile();
        }
    }

    public void run() {
        Socket connection;
        while (!Thread.interrupted()) {
            try {
                // attesa richiesta connessione da parte del client (attesa massima 1s)
                connection = server.accept();
                System.out.println("Connessione richiesta da: " + connection.getInetAddress().toString() + ":" + connection.getPort());
                Thread client = new WarehouseThread(connection, product_catalog);
                client.start();
            }
            catch (SocketTimeoutException exception) {}
            catch (IOException exception) {}
        }
        try {
            server.close();
        }
        catch (IOException exception) {
        }
    }

    public static void main(String[] args) {
        try {
            WarehouseServer server = new WarehouseServer(SERVER_PORT);
            server.start();
            System.in.read();
            server.interrupt();
            server.join();
        }
        catch (IOException exception) {}
        catch (InterruptedException exception) {}
    }
}
