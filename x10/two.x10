public class Driver {
public class PrefixSum {
 val prefixSumArray: Array[Int](1);
 public def this(length:Int) {
 prefixSumArray = (new Array[Int](1..length, (Point)=>0));
 for ([i] in prefixSumArray) {
 prefixSumArray(i) = i;
 }
 }
  public def computeSum()
 {
 val chunkSize = 4;
 val tempArray = new Array[Int](1..prefixSumArray.size(), (Point)=>0);
 val numSteps = <snip> as Int;
 for ([stepNumber] in 1..numSteps) {
 val stepWidth = Math.pow(2, (stepNumber - 1)) as Int;
 val numActivities = Math.ceil(numChunks) as Int;
 Console.OUT.println("numActivities = "+numActivities);
 finish {
 for ([activityId] in 1..numActivities) {
 async {
 for ((j) in low..hi) {
 tempArray(j) = prefixSumArray(j) + prefixSumArray(j-stepWidth);
 }
 }
 }
 public static def main(args: Array[String](1)): Void {
 val arraySize = 5; 						
 Console.OUT.println("PrefixSum test:");
 val psObject = new PrefixSum(arraySize);
 val beforePS = psObject.str();
 Console.OUT.println("Initial array: "+beforePS);
 psObject.computeSum();
 val afterPS = psObject.str();
 Console.OUT.println("After prefix sum: "+afterPS);
 }
}