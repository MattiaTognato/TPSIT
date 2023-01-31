import java.net.*;
import java.io.*;
import java.nio.*;
import java.util.*;

class Server implements Runnable {

    private DatagramSocket socket;

    public Server(int port) throws SocketException {
        socket = new DatagramSocket(port);
        socket.setSoTimeout(1000);
    }

    public void run() {
        DatagramPacket answer;
        byte[] buffer = new byte[1024];
        ByteBuffer data;
        DatagramPacket request = new DatagramPacket(buffer, buffer.length);

        while (!Thread.interrupted()) {
            try {
                socket.receive(request);

                Date now = new Date();
                long timestamp = now.getTime() / 1000;

                data = ByteBuffer.wrap(buffer, 0, 8);
                data.putLong(timestamp);
                answer = new DatagramPacket(data.array(), 8, request.getAddress(), request.getPort());
                socket.send(answer);
            } catch (IOException exception) {}
        }
    }

    public static void main(String[] args) throws IOException {
        Thread thread;
        try {
            Server server = new Server(7777);
            thread = new Thread(server);
            thread.start();
            thread.interrupt();
            thread.join();
        } catch (SocketException | InterruptedException e) {}
    }
}