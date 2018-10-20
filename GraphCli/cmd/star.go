package cmd

import (
	"log"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/spf13/cobra"
)

func init() {
	createCmd.AddCommand(starCmd)
}

var starCmd = &cobra.Command{
	Use:   "star",
	Short: "Create star graph",
	Run: func(cmd *cobra.Command, args []string) {
		g, err := graph.New(vertices)
		if err != nil {
			log.Fatalf("Error creating graph: %v", err)
		}

		for i := 1; i < vertices; i++ {
			g.AddEdge(i, 0)
		}
		exportGraph(g)
	},
}
