package cmd

import (
	"io/ioutil"
	"log"
	"os"
	"os/exec"
	"strconv"

	"github.com/TheMacies/CommonSubgraph/GraphCli/graph"
	"github.com/awalterschulze/gographviz"
	"github.com/spf13/cobra"
)

var (
	input string
)

func init() {
	rootCmd.AddCommand(showCmd)
	showCmd.Flags().StringVarP(&input, "input", "i", "", "path to file containing graph")
	showCmd.MarkFlagRequired("input")
}

var showCmd = &cobra.Command{
	Use:   "show",
	Short: "Show graph using xdot",
	Run: func(cmd *cobra.Command, args []string) {
		f, err := os.Open(input)
		if err != nil {
			log.Fatalf("Could not open file: %v", err)
		}
		defer f.Close()

		imported, err := graph.Import(f)
		if err != nil {
			log.Fatalf("Could not import graph: %v", err)
		}

		graphviz := getGraphvizFromGraph(imported)

		tmpFile, err := ioutil.TempFile(".", "")
		if err != nil {
			log.Fatalf("Could not create tmp file for dot file: %v", err)
		}
		defer tmpFile.Close()
		defer os.Remove(tmpFile.Name())
		ioutil.WriteFile(tmpFile.Name(), []byte(graphviz.String()), 0666)

		xdotCmd := exec.Command("xdot", tmpFile.Name())
		if err = xdotCmd.Run(); err != nil {
			log.Print(err.Error())
		}
	},
}

func getGraphvizFromGraph(g *graph.Builder) *gographviz.Graph {
	graphAst, _ := gographviz.ParseString(`graph G {}`)
	graph := gographviz.NewGraph()
	if err := gographviz.Analyse(graphAst, graph); err != nil {
		panic(err)
	}

	for i := 0; i < len(g.AdjMatrix); i++ {
		graph.AddNode("G", nodeIDFromIndex(i), nil)
	}

	for i := 0; i < len(g.AdjMatrix); i++ {
		for j := 0; j < len(g.AdjMatrix); j++ {
			if g.AdjMatrix[i][j] > 0 {
				graph.AddEdge(nodeIDFromIndex(i), nodeIDFromIndex(j), false, nil)
			}
		}
	}

	return graph
}

func nodeIDFromIndex(idx int) string {
	return "node_" + strconv.Itoa(idx)
}
