private def findTopCandidates(chunk: KoreanToken, profile: TokenizerProfile) = {
  val directMatch: Seq[Seq[KoreanToken]] = findDirectMatch(chunk)

  // Buffer for solutions
  val solutions: util.HashMap[Int, List[CandidateParse]] = new java.util.HashMap[Int, List[CandidateParse]]

  // Initial state
  solutions.put(0, List(CandidateParse(ParsedChunk(Seq[KoreanToken](), 1, profile), koreanPosTrie, ending = None)))

  // Find N best parses per state
  for (end <- 1 to chunk.length; start <- end - 1 to(Seq(end - MAX_TRACE_BACK, 0).max, -1)) {
    val word = chunk.text.slice(start, end)

    // Removing unused solutions from solutions hashmap as the chunk is getting processed
    removeUnusedSolutions(start, end, solutions)

    val curSolutions = solutions.get(start)

    val candidates = curSolutions.flatMap {
      solution =>
      val possiblePoses: Seq[PossibleTrie] = if (solution.ending.isDefined) {
         solution.curTrie.map(t => PossibleTrie(t, 0)) ++ koreanPosTrie.map(t => PossibleTrie(t, 1))
      } else {
        solution.curTrie.map(t => PossibleTrie(t, 0))
      }
      possiblePoses.view.filter {
        t =>
        t.curTrie.curPos == Noun || koreanDictionary.get(t.curTrie.curPos).contains(word.toCharArray)
      }.map { t: PossibleTrie =>
        val candidateToAdd = if (t.curTrie.curPos == Noun && !koreanDictionary.get(Noun).contains(word.toCharArray)) {
          val isWordName: Boolean = isName(word)
          val isWordKoreanNameVariation: Boolean = isKoreanNameVariation(word)

          val unknown = !isWordName && !isKoreanNumber(word) && !isWordKoreanNameVariation
          val pos = Noun
          ParsedChunk(Seq(KoreanToken(word, pos, chunk.offset + start, word.length, unknown = unknown)),t.words, profile)
        } else {
          val pos = t.curTrie.curPos
          ParsedChunk(Seq(KoreanToken(word, pos, chunk.offset + start, word.length)), t.words, profile)
        }

        val nextTrie = t.curTrie.nextTrie.map {
          case nt: KoreanPosTrie if nt == selfNode => t.curTrie
          case nt: KoreanPosTrie => nt
        }

        CandidateParse(solution.parse ++ candidateToAdd, nextTrie, t.curTrie.ending)
      }
    }
    
    val currentSolutions = if (solutions.containsKey(end)) solutions.get(end) else List()
    solutions.put(end, (currentSolutions ++ candidates).sortBy {
      c => (c.parse.score, c.parse.posTieBreaker)
    }.take(TOP_N_PER_STATE))
  }



  val topCandidates: Seq[Seq[KoreanToken]] = if (solutions.get(chunk.length).isEmpty) {
    // If the chunk is not parseable, treat it as a unknown noun chunk.
    Seq(Seq(KoreanToken(chunk.text, Noun, 0, chunk.length, unknown = true)))
  } else {
    // Return the best parse of the final state
    solutions.get(chunk.length).sortBy(c => c.parse.score).map { p => p.parse.posNodes }
  }
  (directMatch ++ topCandidates).distinct
}