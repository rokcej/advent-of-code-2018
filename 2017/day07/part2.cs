namespace Day07;

class Part2 {

	private class Node {
		public Node(string id, int weight) {
			id_ = id;
			weight_ = weight;
			total_weight_ = weight;
		}

		public void AddChild(Node child) {
			child.parent_ = this;
			children_.Add(child);

			Node? temp = this;
			while (temp != null) {
				temp.total_weight_ += child.total_weight_;
				temp = temp.parent_;
			}
		}

		public string id_;
		public int weight_;
		public int total_weight_;

		public Node? parent_ = null;
		public List<Node> children_ = new List<Node>();
	}

	public static void Run() {
		string[] lines = File.ReadAllLines("input");

		Dictionary<string, Node> nodes = new Dictionary<string, Node>();
		Dictionary<string, string[]> edges = new Dictionary<string, string[]>();

		// Parse nodes and edges
		foreach (string line in lines) {
			string[] parts = line.Split(" -> ");

			int i = parts[0].IndexOf(' ');
			string id = parts[0].Substring(0, i);
			int weight = int.Parse(parts[0].Substring(i + 2, parts[0].Length - i - 3));
			nodes[id] = new Node(id, weight);

			if (parts.Length == 2) {
				edges[id] = parts[1].Split(", ");
			}
		}

		// Connect nodes
		foreach (var edge in edges) {
			Node parent = nodes[edge.Key];
			foreach (string child_id in edge.Value) {
				parent.AddChild(nodes[child_id]);
			}
		}

		// Find correct weight
		Node root = nodes.First().Value;
		while (root.parent_ != null) {
			root = root.parent_;
		}
		Console.WriteLine(GetCorrectWeight(root));
	}

	private static int GetCorrectWeight(Node node) {
		if (node.children_.Count == 0) {
			return -1;
		}

		// Find correct total weight
		int total_weight = node.children_[0].total_weight_;
		if (node.children_.Count() > 2) {
			if (total_weight != node.children_[1].total_weight_) {
				total_weight = node.children_[2].total_weight_;
			}
		}

		// Find imbalanced child
		foreach (Node child in node.children_) {
			if (child.total_weight_ == total_weight) {
				continue;
			}
			// Check if child's descendants need to be corrected
			int result = GetCorrectWeight(child);
			if (result != -1) {
				return result;
			}
			// Current child needs to be corrected
			return total_weight - (child.total_weight_ - child.weight_);
		}

		return -1;
	}

}
