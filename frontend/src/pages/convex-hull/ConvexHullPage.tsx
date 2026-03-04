import { useState } from 'react'
import { useOutletContext } from 'react-router-dom'
import Canvas from '../../components/Canvas'
import { fetchSlowConvexHull, fetchConvexHullGrahamScan, fetchConvexHullJarvisMarch } from '../../api/convexHull'
import type { Point2D, Polygon2D, Theme } from '../../types'

type Algorithm = 'slow' | 'graham-scan' | 'jarvis-march'

const ALGORITHM_LABELS: Record<Algorithm, string> = {
  'slow': 'Slow',
  'graham-scan': "Graham's Scan",
  'jarvis-march': 'Jarvis March',
}

export default function ConvexHullPage() {
  const { theme } = useOutletContext<{ theme: Theme }>()
  const [points, setPoints] = useState<Point2D[]>([])
  const [hull, setHull] = useState<Polygon2D | null>(null)
  const [algorithm, setAlgorithm] = useState<Algorithm>('slow')

  function handlePointClick(p: Point2D) {
    setPoints(prev => [...prev, p])
    setHull(null)
  }

  async function calculateConvexHull() {
    if (points.length < 3) return
    let result: Polygon2D
    switch (algorithm) {
      case 'slow':
        result = await fetchSlowConvexHull(points)
        break
      case 'graham-scan':
        result = await fetchConvexHullGrahamScan(points)
        break
      case 'jarvis-march':
        result = await fetchConvexHullJarvisMarch(points)
        break
    }
    setHull(result)
  }

  function reset() {
    setPoints([])
    setHull(null)
  }

  const pointEntries = points.map((p, i) => ({
    point: p,
    label: String(i + 1),
    color: 'royalblue',
  }))

  return (
    <div>
      <div style={{ display: 'flex', alignItems: 'center', gap: 16, marginBottom: 8 }}>
        <h2 style={{ margin: 0 }}>Convex Hull</h2>
        <select
          value={algorithm}
          onChange={e => setAlgorithm(e.target.value as Algorithm)}
        >
          {(Object.keys(ALGORITHM_LABELS) as Algorithm[]).map(key => (
            <option key={key} value={key}>{ALGORITHM_LABELS[key]}</option>
          ))}
        </select>
      </div>

      <p style={{ color: theme.tickText, marginBottom: 16 }}>
        Click points on the canvas, then click Calculate to compute the convex hull.
      </p>

      <Canvas points={pointEntries} onPointClick={handlePointClick} theme={theme} polygon={hull ?? undefined} />

      <div style={{ marginTop: 16, display: 'flex', gap: 12, alignItems: 'center' }}>
        {points.length >= 3 && (
          <button onClick={calculateConvexHull}>Calculate</button>
        )}
        {points.length > 0 && (
          <button onClick={reset}>Reset</button>
        )}
        {hull && (
          <span style={{ color: theme.tickText }}>
            Hull: {hull.vertices.length} vertices
          </span>
        )}
      </div>
    </div>
  )
}
