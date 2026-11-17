import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Scanner;

class MeetingRoom {
    int start;
    int end;

    public MeetingRoom(int start, int end) {
        this.start = start;
        this.end = end;
    }

    public int getEnd() {
        return end;
    }

    @Override
    public String toString() {
        return String.format("(%d, %d)", start, end);
    }
}

public class MeetingRooms {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        List<MeetingRoom> rooms = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            rooms.add(new MeetingRoom(in.nextInt(), in.nextInt()));
        }
        rooms.sort(Comparator.comparing(MeetingRoom::getEnd));
        List<MeetingRoom> chosen = new ArrayList<>();
        int lastEnd = Integer.MIN_VALUE;
        for (MeetingRoom r : rooms) {
            if (r.start >= lastEnd) {   // fits after the last chosen one
                chosen.add(r);
                lastEnd = r.end;
            }
        }
        System.out.println(chosen.size());
        System.out.println(chosen);
    }
}
