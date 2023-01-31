import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;

public class Client {
    private DatagramSocket socket;

    public Client() throws SocketException {
        socket = new DatagramSocket();
        socket.setSoTimeout(1000);
    }

    public void closeSocket() {
        socket.close();
    }

    public long getTime(String host, int port) throws UnknownHostException, IOException, SocketTimeoutException {
        ByteBuffer input, output;
        byte[] buffer = new byte[1024];
        DatagramPacket datagram;
        InetAddress address = InetAddress.getByName(host);
        
        if (socket.isClosed()) { throw new IOException(); }
        
        output = ByteBuffer.allocate(2);
        output.putChar('?');
        
        datagram = new DatagramPacket(output.array(), 2, address, port);
        socket.send(datagram);
        
        datagram = new DatagramPacket(buffer, buffer.length);
        socket.receive(datagram);

        if (datagram.getAddress().equals(address) && datagram.getPort() == port) 
        {
            input = ByteBuffer.wrap(datagram.getData());
            return input.getLong();
        }
        else { throw new SocketTimeoutException(); }
    }

    public static void main(String args[]) {
        String IP = "127.0.0.1";
        int PORT = 7777;
        long timestamp;
        Client client;
        try {
            client = new Client();
            timestamp = client.getTime(IP, PORT);
            System.out.println("Risposta: " + timestamp);
            client.closeSocket();
        } catch (IOException e) {
            System.out.println("ERROR");
        }
    }
}