//package midterms.m1;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

class Candidate {
    private String id;
    private Set<String> skills;

    public Candidate(String id, List<String> skills) {
        this.id = id;
        this.skills = new HashSet<>(skills);
    }

    public static Candidate createCandidate(String line) {
        String[] parts = line.trim().split("\\s+");
        String id = parts[0];
        List<String> skills = new ArrayList<>();
        for (int i = 1; i < parts.length; i++) {
            skills.add(parts[i]);
        }
        return new Candidate(id, skills);
    }

    public int countMatches(List<String> required) {
        int count = 0;
        for (String skill : skills) {
            if (required.contains(skill)) {
                count++;
            }
        }
        return count;
    }

    public String getId() {
        return id;
    }
}

class SkillsMatcher {
    List<String> requiredSkills;
    List<Candidate> candidates = new ArrayList<>();
    public SkillsMatcher(List<String> requiredSkills){
        this.requiredSkills=new ArrayList<>(requiredSkills);
    }

    public void evaluateCandidates(InputStream is, OutputStream os) {
        BufferedReader br = new BufferedReader(new InputStreamReader(is));
        candidates = br.lines().map(Candidate::createCandidate).collect(Collectors.toList());
        candidates.sort((a, b) -> Integer.compare(b.countMatches(requiredSkills), a.countMatches(requiredSkills)));
        PrintWriter pw = new PrintWriter(os);
        for (Candidate candidate : candidates) {
            pw.println(String.format("%s %d", candidate.getId(), candidate.countMatches(requiredSkills)));
        }
        pw.flush();
    }
}

public class SkillsMatcherTest {

    public static void wtf(Scanner in) throws FileNotFoundException {
        PrintWriter pw = new PrintWriter(new FileOutputStream("input.txt"));
        while (in.hasNextLine()) {
            pw.println(in.nextLine());
        }
        pw.flush();
        pw.close();
        in.close();
    }

    public static void main(String[] args) throws IOException {

        Scanner sc = new Scanner(System.in);


        List<String> required = Arrays.stream(sc.nextLine().split(";"))
                .collect(Collectors.toList());


        wtf(sc);

        SkillsMatcher matcher = new SkillsMatcher(required);


        matcher.evaluateCandidates(new FileInputStream("input.txt"), System.out);
    }
}
