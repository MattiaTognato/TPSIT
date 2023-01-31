import java.io.*;
import java.net.*;
import java.util.*;

public class WarehouseThread extends Thread {
    final private Socket connection;
    final private InputStream input;
    final private OutputStreamWriter output;
    final private HashMap<Long, Product> product_catalog;
    private TextFile product_list;

    public WarehouseThread(Socket connection, HashMap<Long, Product> product_catalog) throws IOException {
        this.product_catalog = product_catalog;
        this.connection = connection;
        input = this.connection.getInputStream();
        output = new OutputStreamWriter(this.connection.getOutputStream());
    }
    private String protocol(String command) {
        String component[];
        long code;
        int quantity;
        Product product;
        
        component = command.split(",");
        if (component[0].equalsIgnoreCase("GET")) { 
          if (component.length != 2) {
            return "ERROR";
          }
          try {
               code = Long.parseLong(component[1]);
               synchronized (product_catalog) {
                product = product_catalog.get(code);
               }
               if (product != null) {
                    return product.getDescription()+","+product.getQuantity()+"\r\n";
               }
              }
           catch (NumberFormatException exception) {
            return "ERROR\r\n";
           }
        }
        else if (component[0].equalsIgnoreCase("SET")) {
            if (component.length != 3) {
              return "ERROR";
            }
            try {
               code = Long.parseLong(component[1]);
               quantity = Integer.parseInt(component[2]);
               synchronized (product_catalog) {
                product = product_catalog.get(code);
                if (product == null) {
                 return "NO PRODUCT\r\n";
                }
                String description = product.getDescription();
                product = new Product(code, description, quantity);
                product_catalog.put(code, product);
                // riscrittura file
                try {
                 product_list = new TextFile("prodotti.csv", 'W');
                 for (Product tmp : product_catalog.values()) {
                    String line = tmp.getCode()+","+tmp.getDescription()+","+tmp.getQuantity();
                    product_list.toFile(line);
                 }
                 product_list.closeFile();
                }
                catch (IOException exception) {}
                catch (FileException exception) {}
                finally {
                 try {
                  product_list.closeFile();
                 }
                 catch (IOException exception) {
                 }
                }
                return "OK\r\n";
               }
            }
            catch (NumberFormatException exception) {}
        } 
        return command;
    }
    
    public void run() {
        int n, i;
        String result;
        String character;
        byte [] buffer = new byte[1024];
        StringBuffer command = new StringBuffer();
        
        try {
            while ((n = input.read(buffer)) != -1) {
                if (n > 0) {
                    for (i=0; i<n; i++) {
                        if (buffer[i] == '\r' || buffer[i] == '\n') {
                            result = protocol(command.toString());
                            output.write(result);
                            output.flush();
                            command = new StringBuffer();
                            break;
                        }
                        else {
                            character = new String(buffer, i, 1, "ISO-8859-1");
                            command.append(character);
                        }
                    }
                }
            }
        }
        catch (IOException exception) {}
        try {
            System.out.println("Connessione chiusa!");
            input.close();
            output.close();
            connection.shutdownInput();
            connection.shutdownOutput();
            connection.close();
        }
        catch (IOException exception) {
        }
    }
}
